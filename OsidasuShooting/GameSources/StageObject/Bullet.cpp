/*!
@file   Bullet.cpp
@brief  弾クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Bullet::OnCreate()
	{
		// 当たり判定の追加
		auto PtrColl = AddComponent<CollisionSphere>();
		// 衝突応答を無視
		PtrColl->SetAfterCollision(AfterCollision::None);

		// 発射方向に正面を向ける
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = XMConvertToDegrees(rad);

		// 寿命の追加
		AddComponent<LifeSpan>(m_lifeSpan);

		// エフェクト
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet");
		efkComp->SetScale(m_transformData.Scale);
		efkComp->SetRotation(m_transformData.Rotation);
		efkComp->Play();

		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate()
	{
		auto transPos = GetTransform()->GetPosition(); //(x,y,z)

		float deltaTime = App::GetApp()->GetElapsedTime();

		transPos += m_direction.normalize() * m_speed * deltaTime;
		GetTransform()->SetPosition(transPos);

		// 位置を同期
		GetComponent<EfkComponent>()->SyncPosition();
	}

	void Bullet::OnDestroy() {
		// オブジェクト削除時にエフェクトも停止
		GetComponent<EfkComponent>()->Stop();
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player") || other->FindTag(L"Bullet"))
			return;
		auto ptr = dynamic_pointer_cast<PlayerBase>(other);
		if (ptr)
			// ノックバック
			ptr->KnockBack(m_direction, m_knockBackAmount, m_owner.lock());
		GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
	}
}
//end basecross