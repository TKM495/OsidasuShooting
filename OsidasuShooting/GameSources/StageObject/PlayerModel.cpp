#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		// �`��R���|�[�l���g�̒ǉ�
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMultiMeshResource(L"Player");
		drawComp->SetOwnShadowActive(true);

		// �e�̒ǉ�
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMultiMeshResource(L"Player");
	}

	void PlayerModel::OnUpdate() {
		// �ʒu���]�𓯊�
		auto ownerTrans = m_owner->GetTransform();
		GetTransform()->SetPosition(ownerTrans->GetPosition() + m_offsetPos);
		GetTransform()->SetQuaternion(ownerTrans->GetQuaternion());
	}
}