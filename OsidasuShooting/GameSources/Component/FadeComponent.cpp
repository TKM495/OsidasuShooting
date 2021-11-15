/*!
@file   FadeComponent.cpp
@brief  フェードコンポーネント実体
 */
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FadeComponent::OnUpdate() {
		// 停止中は何もしない
		if (!m_bActive) {
			return;
		}

		auto draw = GetGameObject()->GetDynamicComponent<SpriteBaseDraw>();
		auto delta = App::GetApp()->GetElapsedTime();

		// フェードの方向に応じた処理
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
			// フェードの処理
			auto alpha = (m_delta / m_fadeTime);
			m_color.w = alpha;
			draw->SetDiffuse(m_color);
		}
		else // フェード終了後
		{
			// 方向に応じて値をクランプ
			switch (m_dir)
			{
			case Direction::FadeIn:
				m_color.w = 1.0f;
				break;
			case Direction::FadeOut:
				m_color.w = 0.0f;
				break;
			default:
				break;
			}
			draw->SetDiffuse(m_color);
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
