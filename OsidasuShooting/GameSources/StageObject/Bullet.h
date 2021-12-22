/*!
@file   Bullet.h
@brief  �e�N���X
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"
#include "PlayerBase.h"

namespace basecross {
	class Bullet : public AdvancedGameObject
	{
		// �e�̈ړ����x
		float m_speed;
		// ����
		float m_lifeSpan;
		// �m�b�N�o�b�N��
		float m_knockBackAmount;
		// �ړ�����
		Vec3 m_direction;
		// �I�[�i�[
		weak_ptr<PlayerBase> m_owner;
	public:
		Bullet(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const Vec3& position, const Vec3& direction)
			:AdvancedGameObject(stage), m_owner(owner),
			m_direction(direction),
			m_speed(25.0f), m_lifeSpan(5.0f),
			m_knockBackAmount(5.0f)
		{
			m_transformData.Position = position;
			m_transformData.Scale = Vec3(0.5f);
		}

		Bullet(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner, const Ray& ray)
			:Bullet(stage, owner, ray.Origin, ray.Direction)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void Reflect(shared_ptr<GameObject>& other);
	};
}