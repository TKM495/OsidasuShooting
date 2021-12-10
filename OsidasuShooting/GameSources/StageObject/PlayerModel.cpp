#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto number = Util::IntToWStr((int)m_owner->GetPlayerNumber() + 1);
		auto modelKey = L"Player" + number;

		// 描画コンポーネントの追加
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMultiMeshResource(modelKey);
		drawComp->SetOwnShadowActive(true);

		// 影の追加
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMultiMeshResource(modelKey);
	}

	void PlayerModel::OnUpdate() {
		// 位置や回転を同期
		auto ownerTrans = m_owner->GetTransform();
		GetTransform()->SetPosition(ownerTrans->GetPosition() + m_offsetPos);
		GetTransform()->SetQuaternion(ownerTrans->GetQuaternion());
	}
}