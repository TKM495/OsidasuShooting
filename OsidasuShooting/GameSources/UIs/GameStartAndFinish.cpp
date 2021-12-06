#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartCountDown::OnCreate() {
		m_number = ObjectFactory::Create<Number>(GetStage(), 3);
		m_number->GetTransform()->SetPosition(m_offsetPos);
		m_startSprite = ObjectFactory::Create<SimpleSprite>(GetStage(), L"Start");
	}
	void StartCountDown::OnUpdate() {
		if (!m_countDownTimer.Count()) {
			m_number->SetValue((int)(m_countDownTimer.GetLeftTime() + 1.0f));
		}
	}

	void StartCountDown::OnDraw() {
		if (!m_countDownTimer.IsTimeUp()) {
			m_number->OnDraw();
		}
		else {
			if (!m_startDisplayTimer.Count()) {
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
		m_finishSprite = ObjectFactory::Create<SimpleSprite>(GetStage(), L"Finish");
	}

	void FinishSprite::OnUpdate() {
	}

	void FinishSprite::OnDraw() {
		m_finishSprite->OnDraw();
	}
}