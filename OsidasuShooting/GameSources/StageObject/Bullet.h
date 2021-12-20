/*!
@file   Bullet.h
@brief  弾クラス
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"
#include "PlayerBase.h"

namespace basecross {
	class Bullet : public AdvancedGameObject
	{
		// 弾の移動速度
		float m_speed;
		// 寿命
		float m_lifeSpan;
		// 威力
		float m_power;
		// 移動方向
		Vec3 m_direction;
		// オーナー
		weak_ptr<PlayerBase> m_owner;
	public:
		Bullet(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const Vec3& direction,
			float power)
			:AdvancedGameObject(stage), m_owner(owner),
			m_direction(direction),
			m_speed(25.0f), m_lifeSpan(5.0f),
			m_power(power)
		{
			m_transformData.Position = owner->GetTransform()->GetPosition();
			m_transformData.Scale = Vec3(0.5f);
		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}