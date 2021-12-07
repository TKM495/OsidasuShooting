/*!
@file   FallDecision.cpp
@brief  触れたら落下判定とするオブジェクトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FallDecision::OnCreate() {
		AddComponent<CollisionObb>();
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