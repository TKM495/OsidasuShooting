/*!
@file   Fade.cpp
@brief  フェードイン、アウト実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Fade::OnCreate() {
		GetStage()->SetSharedGameObject(L"Fade", GetThis<Fade>());

		// 画面サイズと同じポリゴンを生成
		auto viewport = GetStage()->GetView()->GetTargetViewport();
		auto halfWidth = viewport.Width / 2.0f;
		auto halfHeight = viewport.Height / 2.0f;

		// ここで白を指定しているのはDiffuseと乗算になるため
		Col4 color(1.0f);
		std::vector<VertexPositionColor> vertices = {
			{Vec3(-halfWidth,+halfHeight, 0.0f), color},
			{Vec3(+halfWidth,+halfHeight, 0.0f), color},
			{Vec3(-halfWidth,-halfHeight, 0.0f), color},
			{Vec3(+halfWidth,-halfHeight, 0.0f), color}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCSpriteDraw>(vertices, indices);
		drawComp->SetDiffuse(Col4(0.0f));
		SetAlphaActive(true);

		// フェードは画面全体に影響するため最も手前に表示する
		SetDrawLayer(10);
	}

	void Fade::OnUpdate() {
		// フェードの処理
		auto pcSprite = GetComponent<PCSpriteDraw>();
		auto delta = App::GetApp()->GetElapsedTime();

		switch (m_state)
		{
		case FadeState::Active:
			// イン、アウトに応じて透明度を変更していく
			m_delta += delta * m_key;
			if (m_delta >= 0 && m_delta <= m_fadeTime) {
				auto alpha = (m_delta / m_fadeTime);
				m_color.w = alpha;
				pcSprite->SetDiffuse(m_color);
			}
			else
			{
				m_state = FadeState::Stop;
				m_delta = 0.0f;
			}
			break;
		case FadeState::Stop:
			break;
		}
	}

	void Fade::FadeIn() {
		m_key = -1;
		m_delta = m_fadeTime;
		m_state = FadeState::Active;
	}

	void Fade::FadeOut() {
		m_key = 1;
		m_delta = 0.0f;
		m_state = FadeState::Active;
	}
}
//end basecross
