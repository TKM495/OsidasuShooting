#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CountDown::OnCreate() {

		redColor = Col4(1.0f, 0.0f, 0.0f, 1.0f);
		m_warningTime = 10.0f;
		expansionMaxRate = 10;//??A10%

		auto stage = GetStage();
		auto blinking = stage->AddGameObject<Blinking>();
		stage->SetSharedGameObject(L"BlinkForCountDown", blinking);
		blinking->SetOriginalColor(redColor);

		currentTime = initialTime;

		Vec3 pos(200.0f, 400.0f, 0.0f);

		CountDownSpriteCreate();

		//�_�ŗp
		m_blinkTime = 0.0f;
		m_blinkTimeChecker = m_blinkTime;
		m_fadeInTime = 0.5f;
		m_fadeOutTime = 0.5f;
		//�_�ŗp..�I��
	}

	// �^�C�}�[�̐������ꕶ�����쐬
	void CountDown::CountDownSpriteCreate() {
		m_numbersOffset = 0;			// �����b�����ʗp
		m_isMinutes = false;			// �����b��
		m_setOffset = Vec3(-102.5f, 360, 0);	// �ꕶ���ڂ̃I�u�W�F�N�g
		m_addOffset = Vec3(45.0f, 0, 0);	// �ꕶ���̑傫��
		m_spaceOffset = Vec3(20.0f, 0, 0);	// ���ƕb�ŕ�����Ƃ��̃X�y�[�X
		m_posOffset = m_setOffset;		// �I�b�t�Z�b�g

		m_scaleValue = 0.7f; 
		m_cur_scaleValue = m_scaleValue;
		m_max_scaleValue = m_scaleValue + m_scaleValue * expansionMaxRate / 100;

		m_scaleOffset = Vec3(m_scaleValue, m_scaleValue, m_scaleValue);

		m_numbers.resize(4);			// ���ƕb��4��������
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

		// �b�A���A���Ԃ̐��l�����߂�
		minutes = (int)(currentTime / 60);
		
		hour = (int)(minutes / 60);
		minutes -= hour * 60;
		seconds = (int)currentTime - (hour * 60 + minutes) * 60;

		// ��ɂ܂Ƃ߂�
		m_timerNumbers = minutes * 100 + seconds;
		/*
		��A
		current time is = 10�b ... �܂�@�O��10�b
		m_timerNumbers = 0010

		current time is = 110�b ... �܂�@1��50�b
		m_timerNumbers = 0150
		*/

		SetTimerNumbers();

		if (currentTime <= m_warningTime)
		{
			auto blinking = GetStage()->GetSharedGameObject<Blinking>(L"BlinkForCountDown");
			auto colon = GetStage()->GetSharedGameObject<Number>(L"ColonForCountDown");
			
			if (m_blinkTime == m_blinkTimeChecker)
			{
				m_blinkTime = m_warningTime;
				blinking->SetToggleTime(m_fadeInTime, m_fadeOutTime, m_blinkTime);
				blinking->SetFading();
				blinking->SetScaling(m_scaleValue, m_max_scaleValue);
				blinking->StartBlinking();

				for (auto& number : m_numbers) {
					number->SetColor(redColor);
				}
				colon->SetColor(redColor);
			}

			float alpha = blinking->GetAdjustedAlpha();
			Col4 color = blinking->GetAdjustedColor();
			Vec3 scale = blinking->GetAdjustedScale();

			if (alpha <= 0)
			{
				alpha = 0.1;
			}

			if (m_timerNumbers <= 0)
			{
				alpha = 1;
				blinking->StopBlinking();
				scale = Vec3(m_scaleValue, m_scaleValue, m_scaleValue);
			}


			for (auto& number : m_numbers) {
				number->SetAlpha(alpha);
				number->SetColor(color);
				auto transform = number->GetComponent<Transform>();
				auto curPosition = transform->GetPosition();
				auto curScale = transform->GetScale();

				Vec3 position = curPosition;
				position.x = curPosition.x / curScale.x * scale.x;

				transform->SetScale(scale);
				transform->SetPosition(position);
			}

			//colon�p
			colon->SetAlpha(alpha);
			colon->SetColor(color);
			auto transform = colon->GetComponent<Transform>();
			auto curPosition = transform->GetPosition();
			auto curScale = transform->GetScale();
			Vec3 position = curPosition;
			position.x = curPosition.x / curScale.x * scale.x;

			transform->SetScale(scale);
			transform->SetPosition(position);
			//colon�p
		}
	}

	void CountDown::OnDraw() {
		GameObject::OnDraw();
		for (auto& number : m_numbers) {
			number->OnDraw();
		}
	}
}