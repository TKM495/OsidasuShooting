#pragma once
#include "stdafx.h"

namespace basecross {
	class Bullet : public StageObject
	{
		float m_speed;
		float m_lifeSpan;
		Vec3 m_direction;
	public:
		Bullet(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& direction)
			:StageObject(stage), m_direction(direction),
			m_speed(25.0f), m_lifeSpan(5.0f)
		{
			m_transformData.Position = position;
			m_transformData.Scale = Vec3(0.5f);
		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}