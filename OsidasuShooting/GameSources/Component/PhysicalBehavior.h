/*!
@file   PhysicalBehavior.h
@brief  �����I�ȋ������s���R���|�[�l���g�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PhysicalBehavior :public Gravity {
		// ���C�W��
		float m_frictionFactor;
		// ���݂̑��x
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
