/*!
@file   FallDecision.cpp
@brief  触れたら落下判定とするオブジェクトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FallDecision::OnCreate() {
		auto obb = AddComponent<CollisionObb>();
		obb->SetDrawActive(true);
		//obb->SetAfterCollision(AfterCollision::None);
	}

	void FallDecision::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto ptr = dynamic_pointer_cast<PlayerBase>(other);
		if (ptr) {
			ptr->Respawn();
		}
		else {
			GetStage()->RemoveGameObject<GameObject>(other);
		}
	}
}