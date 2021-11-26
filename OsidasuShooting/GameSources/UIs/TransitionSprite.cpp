#include "stdafx.h"
#include "Project.h"

namespace basecross {
	shared_ptr<TransitionSprite> TransitionSprite::m_ownInstance = nullptr;

	void TransitionSprite::OnCreate() {
		CreateInstance();

		// ��ʃT�C�Y�Ɠ����|���S���𐶐�
		auto viewport = GetStage()->GetView()->GetTargetViewport();
		auto halfWidth = viewport.Width / 2.0f;
		auto halfHeight = viewport.Height / 2.0f;

		// �����Ŕ����w�肵�Ă���̂�Diffuse�Ə�Z�ɂȂ邽��
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

		// �t�F�[�h�͉�ʑS�̂ɉe�����邽�ߍł���O�ɕ\������
		SetDrawLayer(100);
	}
}