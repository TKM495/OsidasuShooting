/*!
@file   FallDecision.cpp
@brief  �G�ꂽ�痎������Ƃ���I�u�W�F�N�g�̎���
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