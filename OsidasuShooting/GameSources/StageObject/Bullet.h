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
		// 弾が有効になるまでの時間計測タイマー
		TimeCounter m_timer;
		// 移動方向
		Vec3 m_direction;
		// 重撃か
		bool m_isHeavyAttack;
		// オーナー
		weak_ptr<PlayerBase> m_owner;
	public:
		Bullet(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const Vec3& direction,
			float power);

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void Reflect(shared_ptr<GameObject>& other);
	};
}