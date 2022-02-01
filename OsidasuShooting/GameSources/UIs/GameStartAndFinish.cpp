#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartCountDown::OnCreate() {
		m_number = ObjectFactory::Create<Number>(GetStage(), 3);
		m_number->GetTransform()->SetPosition(m_offsetPos);

		m_uiEffect = ObjectFactory::Create<UIEffect>(GetStage(),
			L"StartEffect", Vec2(5, 6), 30);
		m_uiEffect->GetTransform()->SetScale(Vec3(2));

		m_startSprite = ObjectFactory::Create<SimpleSprite>(
			GetStage(), L"Start", TransformData(Vec3(0), Vec3(1.2f)));

		auto trigger = AddComponent<OnceTrigger>();
		trigger->SetFunction(L"Start",
			[] {
				SoundManager::GetInstance()->Play(L"StartSE");
			}
		);
	}
	void StartCountDown::OnUpdate() {
		auto trigger = GetComponent<OnceTrigger>();

		if (!m_countDownTimer.Count()) {
			auto number = (int)(m_countDownTimer.GetLeftTime() + 1.0f);
			m_number->SetValue(number);
			if (number != m_lastValue && number != 0) {
				SoundManager::GetInstance()->Play(L"CountDownSE");
			}
			m_lastValue = number;
		}
		if (m_countDownTimer.IsTimeUp()) {
			m_uiEffect->OnUpdate();
			m_uiEffect->SetUpdateActive(true);
			trigger->LaunchFunction(L"Start");
		}
	}

	void StartCountDown::OnDraw() {
		if (!m_countDownTimer.IsTimeUp()) {
			m_number->OnDraw();
		}
		else {
			if (!m_startDisplayTimer.Count()) {
				m_uiEffect->OnDraw();
				m_startSprite->OnDraw();
			}
			else {
				SetActive(false);
			}
		}
	}

	//--------------------------------------------------------------
	//--------------------------------------------------------------

	void FinishSprite::OnCreate() {
		m_finishSprite = ObjectFactory::Create<SimpleSprite>(
			GetStage(), L"Finish", TransformData(Vec3(0), Vec3(1.2f)));

		m_uiEffect = ObjectFactory::Create<UIEffect>(GetStage(),
			L"StartEffect", Vec2(5, 6), 30);
		m_uiEffect->GetTransform()->SetScale(Vec3(2));
		m_uiEffect->SetUpdateActive(true);
		SoundManager::GetInstance()->Play(L"FinishSE");
	}

	void FinishSprite::OnUpdate() {
		m_uiEffect->OnUpdate();
	}

	void FinishSprite::OnDraw() {
		m_uiEffect->OnDraw();
		m_finishSprite->OnDraw();
	}
}