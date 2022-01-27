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
	}
	void StartCountDown::OnUpdate() {
		if (!m_countDownTimer.Count()) {
			m_number->SetValue((int)(m_countDownTimer.GetLeftTime() + 1.0f));
		}
		if (m_countDownTimer.IsTimeUp()) {
			m_uiEffect->OnUpdate();
			m_uiEffect->SetUpdateActive(true);
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
	}

	void FinishSprite::OnUpdate() {
		m_uiEffect->OnUpdate();
	}

	void FinishSprite::OnDraw() {
		m_uiEffect->OnDraw();
		m_finishSprite->OnDraw();
	}
}