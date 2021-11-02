/*!
@file   Player.cpp
@brief  ƒvƒŒƒCƒ„[‚ÌÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<Gravity>();
		AddComponent<CollisionSphere>();
		ObjectSetUp();
	}

	void Player::OnUpdate() {
		Vec3 dir(0.0f);
		if (App::GetApp()->GetInputDevice().GetKeyState().m_bPushKeyTbl['D'])
			dir += Vec3(0.2f, 0.0f, 0.0f);
		if (App::GetApp()->GetInputDevice().GetKeyState().m_bPushKeyTbl['A'])
			dir += Vec3(-0.2f, 0.0f, 0.0f);

		auto pos = GetTransform()->GetPosition();
		GetTransform()->SetPosition(pos + dir);
	}
}