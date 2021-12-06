#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto number = Util::IntToWStr((int)m_owner->GetPlayerNumber() + 1);
		auto modelKey = L"Player" + number;

		// �`��R���|�[�l���g�̒ǉ�
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMultiMeshResource(modelKey);
		drawComp->SetOwnShadowActive(true);

		// �e�̒ǉ�
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMultiMeshResource(modelKey);
	}

	void PlayerModel::OnUpdate() {
		// �ʒu���]�𓯊�
		auto ownerTrans = m_owner->GetTransform();
		GetTransform()->SetPosition(ownerTrans->GetPosition() + m_offsetPos);
		GetTransform()->SetQuaternion(ownerTrans->GetQuaternion());
	}
}