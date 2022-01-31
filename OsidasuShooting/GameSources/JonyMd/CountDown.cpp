#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CountDown::OnCreate() 
	{
		redColor = Col4(1.0f, 0.0f, 0.0f, 1.0f);
		m_warningTime = 10.0f;
		expansionMaxRate = 10;//例　10%

		initialTime = 32; //temporary
		currentTime = initialTime;

		Vec3 pos(200.0f, 400.0f, 0.0f);

		CountDownSpriteCreate();

		BlinkingCreation();
		RemainingSpriteCreation();
	}

	// タイマーの数字を一文字ずつ作成
	void CountDown::CountDownSpriteCreate() {
		m_numbersOffset = 0;			// 分か秒か判別用
		m_isMinutes = false;			// 分か秒か
		m_setOffset = Vec3(-102.5f, 360, 0);	// 一文字目のオブジェクト
		m_addOffset = Vec3(45.0f, 0, 0);	// 一文字の大きさ
		m_spaceOffset = Vec3(20.0f, 0, 0);	// 分と秒で分けるときのスペース
		m_posOffset = m_setOffset;		// オッフセット

		m_scaleValue = 0.7f; 
		m_cur_scaleValue = m_scaleValue;
		m_max_scaleValue = m_scaleValue + m_scaleValue * expansionMaxRate / 100;

		m_scaleOffset = Vec3(m_scaleValue, m_scaleValue, m_scaleValue);

		m_numbers.resize(4);			// 分と秒で4文字ずつ
		for (auto& number : m_numbers) {
			++m_numbersOffset;

			number = ObjectFactory::Create<Number>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(m_posOffset);
			numberTrans->SetScale(m_scaleOffset);

			m_posOffset += m_addOffset;

			if (m_numbersOffset == 2 && !m_isMinutes) {
				m_isMinutes = false;
				m_posOffset += m_spaceOffset;
				AddTimerColonSpriteCreate(m_posOffset, m_scaleOffset);
			}
			numberTrans->SetPivot(GetComponent<Transform>()->GetPosition());
		}
	}

	void CountDown::AddTimerColonSpriteCreate(Vec3 posValue, Vec3 scaleValue) {
		auto colon = GetStage()->AddGameObject<Number>(10);
		GetStage()->SetSharedGameObject(L"ColonForCountDown", colon);
		auto colonTrans = colon->GetComponent<Transform>();
		auto posSetting(-m_spaceOffset * 1.6f);
		colonTrans->SetPosition(posValue + posSetting);
		colonTrans->SetScale(scaleValue);
	}

	void CountDown::SetTimerNumbers() {
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		int place = static_cast<int>(pow(10, m_numbers.size() - 1));
		for (auto& number : m_numbers) {
			int value = m_timerNumbers / place % 10;
			place /= 10;

			number->SetValue(value);
		}
	}

	void CountDown::OnUpdate() {
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		if (reset)
		{
			currentTime = initialTime;
			reset = false;
		}

		if (start)
		{
			currentTime -= deltaTime;
		}

		UpdatingTimers();
		SetTimerNumbers();

		BlinkingProcess();

		RemainingSpriteShowing();
	}

	void CountDown::OnDraw()
	{
		GameObject::OnDraw();
		for (auto& number : m_numbers) {
			number->OnDraw();
		}
	}

	void CountDown::UpdatingTimers()
	{
		int minutes;
		int hour;
		int seconds;

		// 秒、分、時間の数値を求める
		minutes = (int)(currentTime / 60);

		hour = (int)(minutes / 60);
		minutes -= hour * 60;
		seconds = (int)currentTime - (hour * 60 + minutes) * 60;

		// 一つにまとめる
		m_timerNumbers = minutes * 100 + seconds;
		/*
		例、
		current time is = 10秒 ... つまり　０分10秒
		m_timerNumbers = 0010

		current time is = 110秒 ... つまり　1分50秒
		m_timerNumbers = 0150
		*/

	}//UpdatingTimers...end



	void CountDown::RemainingSpriteCreation()
	{
		remaining10sec = GetStage()->AddGameObject<SimpleSprite>(L"Remaining10Sec");
		remaining20sec = GetStage()->AddGameObject<SimpleSprite>(L"Remaining20Sec");
		remaining30sec = GetStage()->AddGameObject<SimpleSprite>(L"Remaining30Sec");

		float screenHeight = 360;
		auto numberSize = Utility::GetTextureSize(L"Number");
		auto objs = GetStage()->GetGameObjectVec();

		float newScale = m_scaleValue * 2.0f;
		numberSize = (numberSize * newScale) / 2;
		Vec3 scale = Vec3(newScale, newScale, newScale);
		for (auto& obj : objs)
		{
			auto remaining = dynamic_pointer_cast<SimpleSprite>(obj);
			if (remaining == remaining10sec || remaining == remaining20sec || remaining == remaining30sec)
			{
				auto drawing = remaining->GetComponent<PCTSpriteDraw>();
				auto transform = remaining->AddComponent<Transform>();

				redColor.w = 0.5;
				drawing->SetDiffuse(redColor);

				remaining->SetDrawActive(false);
				transform->SetScale(scale);

				Vec3 position = transform->GetPosition();
				//auto halfSize = remaining->GetHalfSize();
				//position.y = screenHeight - halfSize.y - numberSize.y;
				transform->SetPosition(position);
			}

		}
	}//RemainingSpriteCreation...end


	void CountDown::RemainingSpriteShowing()
	{
		remaining30sec->SetDrawActive(false);
		remaining20sec->SetDrawActive(false);
		remaining10sec->SetDrawActive(false);
		if (currentTime <= 30.999 && currentTime >= 28)
		{
			remaining30sec->SetDrawActive(true);
		}
		else if (currentTime <= 20.999 && currentTime >= 18)
		{
			remaining20sec->SetDrawActive(true);
		}
		else if (currentTime <= 10.999 && currentTime >= 8)
		{
			remaining10sec->SetDrawActive(true);
		}
	}//RemainingSpriteShowing...end


	void CountDown::BlinkingCreation()
	{
		auto stage = GetStage();
		auto blinking = stage->AddGameObject<Blinking>();
		stage->SetSharedGameObject(L"BlinkForCountDown", blinking);
		blinking->SetOriginalColor(redColor);


		//点滅用
		m_blinkTime = 0.0f;
		m_blinkTimeChecker = m_blinkTime;
		m_fadeInTime = 0.5f;
		m_fadeOutTime = 0.5f;
		//点滅用..終了

	}//BlinkingCreation...end

	void CountDown::BlinkingProcess()
	{

		auto blinking = GetStage()->GetSharedGameObject<Blinking>(L"BlinkForCountDown");
		auto colon = GetStage()->GetSharedGameObject<Number>(L"ColonForCountDown");

		BlinkingProcessStart();

		if (m_timerNumbers == 0 && !isContinuousIncreasion && !doAdjustScale)
		{
			blinking->SetToggleTime(m_fadeInTime, m_fadeOutTime, m_blinkTime);
			blinking->SetScaling(m_scaleValue, m_max_scaleValue);
			blinking->StartBlinking();

			doAdjustScale = true;
		}

		BlinkingProcessContinuation();

	}//BlinkingProcess...end



	void CountDown::BlinkingProcessStart()
	{
		auto blinking = GetStage()->GetSharedGameObject<Blinking>(L"BlinkForCountDown");
		auto colon = GetStage()->GetSharedGameObject<Number>(L"ColonForCountDown");
		if (currentTime <= m_warningTime && m_warningTime > 0)
		{

			if (m_blinkTime == m_blinkTimeChecker)
			{
				m_blinkTime = m_warningTime;
				blinking->SetToggleTime(m_fadeInTime, m_fadeOutTime, m_blinkTime);
				blinking->SetFading();
				blinking->SetScaling(m_scaleValue, m_max_scaleValue);
				blinking->StartBlinking();

				for (auto& number : m_numbers) {
					number->SetColor(redColor);
					number->GetComponent<Transform>()->SetScale(Vec3(m_scaleValue, m_scaleValue, m_scaleValue));
				}
				colon->SetColor(redColor);
				colon->GetComponent<Transform>()->SetScale(Vec3(m_scaleValue, m_scaleValue, m_scaleValue));
			}


			if (m_timerNumbers <= 0)
			{
				blinking->StopBlinking();
				isContinuousIncreasion = true;
				m_warningTime = 0;
			}
			else
			{
				doAdjustAlpha = true;
				doAdjustColor = true;
				doAdjustScale = true;
			}

		}
	}//BlinkingProcessStart...end

	void CountDown::BlinkingProcessContinuation()
	{
		auto blinking = GetStage()->GetSharedGameObject<Blinking>(L"BlinkForCountDown");
		auto colon = GetStage()->GetSharedGameObject<Number>(L"ColonForCountDown");

		if (doAdjustAlpha || doAdjustColor || doAdjustScale)
		{
			float alpha = blinking->GetAdjustedAlpha();
			Col4 color = blinking->GetAdjustedColor();
			Vec3 scale = blinking->GetAdjustedScale();

			if (alpha <= 0)
			{
				alpha = 0.01;
			}

			for (auto& number : m_numbers) {
				if (doAdjustAlpha) { number->SetAlpha(alpha); }
				if (doAdjustColor) { number->SetColor(color); }


				if (doAdjustScale)
				{
					auto transform = number->GetComponent<Transform>();
					auto curPosition = transform->GetPosition();
					auto curScale = transform->GetScale();

					Vec3 position = curPosition;
					position.x = curPosition.x / curScale.x * scale.x;

					transform->SetScale(scale);
					transform->SetPosition(position);
				}
			}

			//colon用
			if (doAdjustAlpha) { colon->SetAlpha(alpha); }
			if (doAdjustColor) { colon->SetColor(color); }

			if (doAdjustScale)
			{
				auto transform = colon->GetComponent<Transform>();
				auto curPosition = transform->GetPosition();
				auto curScale = transform->GetScale();
				Vec3 position = curPosition;
				position.x = curPosition.x / curScale.x * scale.x;

				transform->SetScale(scale);
				transform->SetPosition(position);
			}
			//colon用


			if (isContinuousIncreasion)
			{
				isContinuousIncreasion = false;
				doAdjustAlpha = false;
				doAdjustColor = false;
				doAdjustScale = false;
			}
		}

	}//BlinkingProcessContinuation...end
}