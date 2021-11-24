/*!
@file   SpecialLaser.cpp
@brief  必殺技の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void SpecialLaser::OnCreate() {
		// 当たり判定の追加
		auto PtrColl = AddComponent<CollisionObb>();
		// 衝突応答を無視
		PtrColl->SetAfterCollision(AfterCollision::None);
		PtrColl->SetDrawActive(true);

		// 発射方向に正面を向ける
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = rad;

		// 位置の調整
		m_transformData.Position.z = m_zPosSet;

		//m_transformData.Position = m_direction.normalize() * -m_zPosSet;
		// 寿命の追加
		//AddComponent<LifeSpan>(m_lifeSpan);

		ObjectSetUp();

		//// エフェクトはオブジェクトの位置の影響を受けるためセットアップのあと
		//auto efkComp = AddComponent<EfkComponent>();
		//efkComp->SetEffectResource(L"Bullet");
		//efkComp->SetScale(m_transformData.Scale);
		//efkComp->SetRotation(m_transformData.Rotation);
		//efkComp->Play();

		AddTag(L"Bullet");

		Debug::GetInstance()->Log(Utility::ConvertRadVecToDegVec(
			GetComponent<Transform>()->GetRotation()));
		Debug::GetInstance()->Log(GetComponent<Transform>()->GetRotation());
		Debug::GetInstance()->Log(GetComponent<Transform>()->GetPivot());
		Debug::GetInstance()->Log(GetComponent<Transform>()->GetWorldPosition());
		Debug::GetInstance()->Log(m_transformData.Position);

		//GetComponent<Transform>()->SetWorldPosition(Vec3(0));
	}

	void SpecialLaser::OnUpdate() {

		auto transPos = GetTransform()->GetPosition(); //(x,y,z)
		float deltaTime = App::GetApp()->GetElapsedTime();

		// 位置を同期
		//GetComponent<EfkComponent>()->SyncPosition();
	}

	void SpecialLaser::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player") || other->FindTag(L"Bullet")) return;
	}
}