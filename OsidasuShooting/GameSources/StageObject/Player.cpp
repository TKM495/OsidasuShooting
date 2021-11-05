/*!
@file   Player.cpp
@brief  プレイヤーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<PhysicalBehavior>();
		AddComponent<CollisionSphere>();

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet");
		efkComp->SetScale(Vec3(1.0f));
		ObjectSetUp();
	}

	void Player::OnUpdate() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto efkComp = GetComponent<EfkComponent>();
		auto physicalComp = GetComponent<PhysicalBehavior>();
		if (keyState.m_bPushKeyTbl['D'])
			physicalComp->Move(Vec3(5.0f, 0.0f, 0.0f));
		if (keyState.m_bPushKeyTbl['A'])
			physicalComp->Move(Vec3(-5.0f, 0.0f, 0.0f));
		if (keyState.m_bPushKeyTbl['W'])
			physicalComp->Move(Vec3(0.0f, 0.0f, 5.0f));
		if (keyState.m_bPushKeyTbl['S'])
			physicalComp->Move(Vec3(0.0f, 0.0f, -5.0f));
		if (keyState.m_bPressedKeyTbl[VK_SPACE])
			efkComp->Play();
		efkComp->AddLocation(Vec3(0.0f, 0.0f, 1.0f));
	}
}