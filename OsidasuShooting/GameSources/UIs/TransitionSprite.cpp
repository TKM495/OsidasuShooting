#include "stdafx.h"
#include "Project.h"

namespace basecross {
	shared_ptr<TransitionSprite> TransitionSprite::m_ownInstance = nullptr;

	void TransitionSprite::OnCreate() {
		CreateInstance();

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

		AddComponent<FadeComponent>()->SetFadeTime(1.0f);

		// フェードは画面全体に影響するため最も手前に表示する
		SetDrawLayer(100);
	}
}