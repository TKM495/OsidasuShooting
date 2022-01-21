/*!
@file   Bullet.cpp
@brief  弾クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Bullet::Bullet(const shared_ptr<Stage>& stage,
		const shared_ptr<PlayerBase>& owner,
		const Vec3& direction,
		float power)
		:AdvancedGameObject(stage), m_owner(owner),
		m_direction(direction),
		m_speed(25.0f), m_lifeSpan(5.0f),
		m_power(power), m_timer(0.1f), m_isHeavyAttack(false)
	{
		m_transformData.Position = owner->GetTransform()->GetPosition();
		m_transformData.Scale = Vec3(0.5f);
	}

	void Bullet::OnCreate()
	{
		// 当たり判定の追加
		auto PtrColl = AddComponent<CollisionSphere>();
		// 衝突応答を無視
		PtrColl->SetAfterCollision(AfterCollision::None);
		// オーナーと弾との当たり判定を無視
		PtrColl->AddExcludeCollisionTag(L"Bullet");

		// 発射方向に正面を向ける
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = XMConvertToDegrees(rad);

		// 寿命の追加
		AddComponent<LifeSpan>(m_lifeSpan);

		// エフェクト
		auto effectTrans = m_transformData;
		effectTrans.Position = Vec3(0.0f, 0.0f, 0.5f);
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet", effectTrans);
		efkComp->IsSyncPosition(L"Bullet", true);
		efkComp->SetEffectResource(L"Hit", effectTrans);
		efkComp->SetEffectResource(L"HeavyHit", effectTrans);
		efkComp->Play(L"Bullet");

		// 影
		AddComponent<CircleShadow>();

		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate() {
		auto transPos = GetTransform()->GetPosition(); //(x,y,z)

		float deltaTime = App::GetApp()->GetElapsedTime();

		transPos += m_direction.normalize() * m_speed * deltaTime;
		GetTransform()->SetPosition(transPos);
		m_timer.Count();
	}

	void Bullet::OnDestroy() {
		// オブジェクト削除時に弾のエフェクトを停止し、
		// ヒット時のエフェクトを再生
		auto efkComp = GetComponent<EfkComponent>();
		efkComp->Stop(L"Bullet");
		if (m_isHeavyAttack)
			efkComp->Play(L"HeavyHit");
		else
			efkComp->Play(L"Hit");
	}

	void Bullet::Reflect(shared_ptr<GameObject>& reflect) {
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();
		auto rot = ptrTrans->GetRotation();

		auto blockTrans = reflect->GetComponent<Transform>();
		auto blockPos = blockTrans->GetPosition();
		auto blockScl = blockTrans->GetScale();
		auto blockHalfSize = 0.4f;

		auto ptrEfk = GetComponent<EfkComponent>();

		auto reverse = -1;

		// 全方向反転

		auto brockSizeX = blockHalfSize * blockScl.x;
		auto brockSizeZ = blockHalfSize * blockScl.z;

		// 横方向反転
		if (pos.x >= blockPos.x + brockSizeX ||
			pos.x <= blockPos.x - brockSizeX) {
			m_direction.x *= reverse;
		}

		// 縦方向反転
		if (pos.z >= blockPos.z + brockSizeZ ||
			pos.z <= blockPos.z - brockSizeZ) {
			m_direction.z *= reverse;
		}

		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		rot.y = rad;

		ptrEfk->SetRotation(L"Bullet", rot);
		ptrTrans->SetRotation(rot);
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Reflector")) {
			Reflect(other);
		}
		else {
			if (other->FindTag(L"Break")) {
				auto breakBlock = dynamic_pointer_cast<BreakBlock>(other);
				breakBlock->BlockDamage(1);
			}
			else {
				auto ptr = dynamic_pointer_cast<PlayerBase>(other);
				if (ptr) {
					// カウントが終わった場合
					if (m_timer.IsTimeUp() || m_owner.lock() != ptr) {
						KnockBackData data(
							KnockBackData::Category::Bullet,
							m_direction, m_power, m_owner
						);
						// ノックバック
						// 結果が1.5より大きい場合は重撃になる
						m_isHeavyAttack = ptr->KnockBack(data) > 1.5f;
					}
					else {
						return;
					}
				}
			}
			// 自身を削除
			Destroy<Bullet>();
		}
	}
}
//end basecross