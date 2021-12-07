/*!
@file   FallDecision.cpp
@brief  �G�ꂽ�痎������Ƃ���I�u�W�F�N�g�̎���
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