#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CountDown::OnCreate() {
		currentTime = initialTime;

		auto transComp = GetComponent<Transform>();
		Vec3 pos(200.0f, 400.0f, 0.0f);
		//transComp->SetScale(0.5f, 0.5f, 0.5f);
		//transComp->SetPosition(pos);

		CountDownSpriteCreate();
	}

	// タイマーの数字を一文字ずつ作成
	void CountDown::CountDownSpriteCreate() {
		int numbersOffset = 0;			// 分か秒か判別用
		bool isMinutes = false;			// 分か秒か
		Vec3 setOffset(-132.5f, 360, 0);	// 一文字目のオブジェクト
		Vec3 addOffset(  45.0f, 0, 0);	// 一文字の大きさ
		Vec3 spaceOffset(20.0f, 0, 0);	// 分と秒で分けるときのスペース
		Vec3 posOffset = setOffset;		// オッフセット
		
		float scaleValue = 0.7f;
		Vec3 scaleOffset(scaleValue, scaleValue, scaleValue);

		m_numbers.resize(4);			// 分と秒で4文字ずつ
		for(auto& number : m_numbers)
		{
			++numbersOffset;

			number = ObjectFactory::Create<Number>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(posOffset);
			numberTrans->SetScale(scaleOffset);
			posOffset += addOffset;

			if (numbersOffset == 2 && !isMinutes)
			{
				isMinutes = false;
				posOffset += spaceOffset;
			}
		}

	}

	
	void CountDown::SetTimerNumbers() {
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		//if (m_timeCount > 1.0f && m_timerNumbers < pow(10, m_numbers.size()) - 1)
		//{

		//}

		// numberに引数を渡す
		int place = static_cast<int>(pow(10, m_numbers.size() - 1));
		for (auto& number : m_numbers)
		{
			int value = m_timerNumbers / place % 10;
			place /= 10;

			number->SetValue(value);
		}

	}


	void CountDown::OnUpdate() {
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		int minutes;
		int hour;
		int seconds;
		
		wstring clocks = L"00:00:00";

		if (reset)
		{
			currentTime = initialTime;
			reset = false;
		}

		if (start)
		{
			currentTime -= deltaTime;
		}

		// 秒、分、時間の数値を求める
		minutes = (int)(currentTime / 60);
		hour = (int)(minutes / 60);
		seconds = (int)currentTime - (hour * 60 + minutes) * 60;

		// 一つにまとめる
		m_timerNumbers = minutes * 100 + seconds;

		//clocks = L"";
		//if (hour <= 9)
		//{
		//	clocks += L"0";
		//}
		//clocks += Util::FloatToWStr(hour) + L":";

		//if (minutes <= 9)
		//{
		//	clocks += L"0";
		//}
		//clocks += Util::FloatToWStr(minutes) + L":";

		//if (seconds <= 9)
		//{
		//	clocks += L"0";
		//}
		//clocks += Util::FloatToWStr(seconds);



		auto m_ssComp = AddComponent<StringSprite>();
		m_ssComp->SetText(clocks);
		
		//m_timerNumbers = minutes * 100 + seconds;	

		SetTimerNumbers();
	}

	void CountDown::OnDraw() {
		GameObject::OnDraw();
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}


}
