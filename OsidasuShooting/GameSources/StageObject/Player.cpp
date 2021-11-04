/*!
@file   Player.cpp
@brief  ÉvÉåÉCÉÑÅ[ÇÃé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<PhysicalBehavior>();
		AddComponent<CollisionSphere>();
		ObjectSetUp();
	}

	void Player::OnUpdate() {
		auto physicalComp = GetComponent<PhysicalBehavior>();
		if (App::GetApp()->GetInputDevice().GetKeyState().m_bPushKeyTbl['D'])
			physicalComp->Move(Vec3(1.0f, 0.0f, 0.0f));
		if (App::GetApp()->GetInputDevice().GetKeyState().m_bPushKeyTbl['A'])
			physicalComp->Move(Vec3(-1.0f, 0.0f, 0.0f));
	}
}