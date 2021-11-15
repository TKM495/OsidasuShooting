#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CountDown::OnCreate()
	{
		currentTime = initialTime;

		auto transComp = GetComponent<Transform>();
		Vec3 pos(200.0f, 400.0f, 0.0f);
		//transComp->SetScale(0.5f, 0.5f, 0.5f);
		transComp->SetPosition(pos);

		CreateCount();
	}

	void CountDown::CreateCount()
	{
		int numbersOffset = 0;			// 分か秒か判別用
		//bool isMinutes = false;		// 分か秒か
		Vec3 setOffset( 130.0f, 0, 0);	// 一文字目のオブジェクト
		Vec3 addOffset(  65.0f, 0, 0);	// 一文字の大きさ
		Vec3 spaceOffset( 14.0f, 0, 0);	// 分と秒で分けるときのスペース
		Vec3 offset = setOffset;		// オッフセット

		m_numbers.resize(4);			// 分と秒で4文字ずつ
		for(auto& number : m_numbers)
		{
			number = ObjectFactory::Create<Number>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(offset);
			offset += addOffset;

			++numbersOffset;
			if (numbersOffset == 2)
			{
				offset += spaceOffset;
				numbersOffset = 0;
			}
		}

	}

	void CountDown::SetTimerNumbers()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		m_timeCount += deltaTime;
		if (m_timeCount > 1.0f && m_timerNumbers < pow(10, m_numbers.size()) - 1)
		{
			m_timeCount = 0.0f;
			m_timerNumbers++;
		}

		int place = static_cast<int>(pow(10, m_numbers.size() - 1));
		for (auto& number : m_numbers)
		{
			int value = m_timerNumbers / place % 10;
			place /= 10;

			number->SetValue(value);
		}

	}


	void CountDown::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		//int minutes;
		//int hour;
		//int seconds;
		
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


		//minutes = (int)(currentTime / 60);
		//hour = (int)(minutes / 60);
		//seconds = (int)currentTime - (hour * 60 + minutes) * 60;

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



		//auto m_ssComp = AddComponent<StringSprite>();
		//m_ssComp->SetText(clocks);
		
		//m_timerNumbers = minutes * 100 + seconds;	

		SetTimerNumbers();
	}

	void CountDown::OnDraw()
	{
		GameObject::OnDraw();
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}


}
