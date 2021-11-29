/*!
@file   SpecialLaser.h
@brief  必殺技
*/

#pragma once
#include "stdafx.h"
#include "PlayerBase.h"

namespace basecross {
	struct SkillData {
		float m_speed;			// 移動速度
		float m_lifeSpan;		// 持続時間
		float m_knokBackAmount;	// ノックバック
		Vec3 m_direction;		// 移動方向あるいは向き

		SkillData() {
			this->m_speed = 0.0f;
			this->m_lifeSpan = 0.0f;
			this->m_knokBackAmount = 0.0f;
			//this->m_direction = Vec3(0.0f);
		}
	};

	class SpecialSkill : public AdvancedGameObject {
	protected:
		virtual void SkillData() = 0;

		weak_ptr<PlayerBase> m_owner;
		Vec3 m_position;
		Vec3 m_direction;
	public:
		SpecialSkill(
			const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const Vec3& position,
			const Vec3& direction)
			: AdvancedGameObject(stage),
			m_owner(owner),
			m_position(position),
			m_direction(direction)
		{
			SetTransformInit(false);
		}

		//void OnCreate() {};
		//void OnUpdate() {};
	};

	class SpecialLaser : public SpecialSkill {
		void SkillData() {};

		Vec3 m_scale;
		Vec3 m_position;

		shared_ptr<PlayerBase> m_owner;

		float m_lifeSpan;
		float m_zPosSet;
	public:
		SpecialLaser(
			const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const Vec3& position,
			const Vec3& direction)
			: SpecialSkill(stage, owner, position, direction),
			m_lifeSpan(3.0f),
			m_zPosSet(20.0f),
			m_owner(owner)
		{
			m_transformData.Position = position;
			//m_transformData.Rotation = Vec3(0,0,0);
			m_transformData.Scale = Vec3(2.0f, 2.0f, m_zPosSet * 2.0f);
		}

		SpecialLaser(
			const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const Ray& ray)
			: SpecialLaser(stage, owner, ray.Origin, ray.Direction)
		{}

		void MoveTestLaser();
		void OnCreate() override;
		void OnUpdate() override;

		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}