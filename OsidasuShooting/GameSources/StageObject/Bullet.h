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
		// �З�
		float m_power;
		// �e���L���ɂȂ�܂ł̎��Ԍv���^�C�}�[
		TimeCounter m_timer;
		// �ړ�����
		Vec3 m_direction;
		// �d����
		bool m_isHeavyAttack;
		// �I�[�i�[
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