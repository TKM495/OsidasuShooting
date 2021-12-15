#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto number = Util::IntToWStr((int)m_owner->GetPlayerNumber() + 1);
		wstring typeKey;
		switch (m_owner->GetPlayerType())
		{
		case PlayerType::Laser:
			typeKey = L"Laser";
			break;
		case PlayerType::Missile:
			typeKey = L"Missile";
			break;
		default:
			throw BaseException(
				L"��`����Ă��Ȃ����������ł��B",
				L"switch (m_owner->GetPlayerType())",
				L"PlayerModel::OnCreate()"
			);
			break;
		}

		auto modelKey = typeKey + L"Player" + number;

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