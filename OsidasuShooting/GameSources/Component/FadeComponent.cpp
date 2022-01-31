/*!
@file   FadeComponent.cpp
@brief  �t�F�[�h�R���|�[�l���g����
 */
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FadeComponent::OnUpdate() {
		// ��~���͉������Ȃ�
		if (!m_bActive) {
			return;
		}

		auto draw = GetGameObject()->GetDynamicComponent<SpriteBaseDraw>();
		auto delta = App::GetApp()->GetElapsedTime();

		// �t�F�[�h�̕����ɉ���������
		switch (m_dir)
		{
		case Direction::FadeIn:
			m_delta += +delta;
			break;
		case Direction::FadeOut:
			m_delta += -delta;
			break;
		default:
			break;
		}

		if (m_delta >= 0 && m_delta <= m_fadeTime) {
			// �t�F�[�h�̏���
			auto alpha = Lerp::CalculateLerp(m_minAlpha, m_maxAlpha, 0, m_fadeTime, m_delta, Lerp::rate::Linear);
			auto color = draw->GetDiffuse();
			color.w = alpha;
			draw->SetDiffuse(color);
		}
		else // �t�F�[�h�I����
		{
			auto color = draw->GetDiffuse();
			// �����ɉ����Ēl���N�����v
			switch (m_dir)
			{
			case Direction::FadeIn:
				color.w = 1.0f;
				break;
			case Direction::FadeOut:
				color.w = 0.0f;
				break;
			default:
				break;
			}
			draw->SetDiffuse(color);
			m_bActive = false;
			m_delta = 0.0f;
		}
	}

	void FadeComponent::FadeOut() {
		m_delta = m_fadeTime;
		m_dir = Direction::FadeOut;
		m_bActive = true;
	}

	void FadeComponent::FadeIn() {
		m_delta = 0.0f;
		m_dir = Direction::FadeIn;
		m_bActive = true;
	}
}
//end basecross