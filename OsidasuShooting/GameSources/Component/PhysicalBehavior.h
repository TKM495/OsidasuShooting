/*!
@file   PhysicalBehavior.h
@brief  物理的な挙動を行うコンポーネントクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PhysicalBehavior :public Gravity {
		// 摩擦係数
		float m_frictionFactor;
		// 現在の速度
		Vec3 m_velocity;
	public:
		PhysicalBehavior(const shared_ptr<GameObject>& gameObjectPtr)
			:Gravity(gameObjectPtr), m_frictionFactor(0.99999f)
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override {}

		void Move(Vec3 acceleration);

		void AddForce(Vec3 force);
	};
}
