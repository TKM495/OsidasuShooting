#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		// 描画コンポーネントの追加
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMultiMeshResource(L"Player");
		drawComp->SetOwnShadowActive(true);

		// 影の追加
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMultiMeshResource(L"Player");
	}

	void PlayerModel::OnUpdate() {
		// 位置や回転を同期
		auto ownerTrans = m_owner->GetTransform();
		GetTransform()->SetPosition(ownerTrans->GetPosition() + m_offsetPos);
		GetTransform()->SetQuaternion(ownerTrans->GetQuaternion());
	}
}