/*!
@file   PhysicalBehavior.h
@brief  �����I�ȋ������s���R���|�[�l���g�N���X
*/

#pragma once
#include "stdafx.h"
#include "Utility/GroundingDecision.h"

namespace basecross {
	class PhysicalBehavior :public Component {
		// ��C��R
		float m_airDrag;
		// �n�ʂ̒�R
		float m_groundDrag;
		// �ő呬�x
		float m_maxSpeed;
		// ���݂̑��x
		Vec3 m_velocity;
		// �������l�i�ړ����x�����̒l��菬�����ꍇ0�Ƃ݂Ȃ��j
		float m_threshold;
		// �m�b�N�o�b�N�̍ő卂�x
		float m_knockBackMaxY;
		// ���Ԕ{��
		float m_timeScale;
		// �ڒn����N���X
		unique_ptr<GroundingDecision> m_groundingDecision;
	public:
		// �R���X�g���N�^
		PhysicalBehavior(const shared_ptr<GameObject>& gameObjectPtr);

		// �R���|�[�l���g�̐���
		void OnCreate()override;
		// �R���|�[�l���g�̍X�V
		void OnUpdate()override;
		// �R���|�[�l���g�̕`��
		void OnDraw()override {}

		/**
		 * @brief �ړ�
		 *
		 * @param force �������
		 */
		void Move(const Vec3& force);
		/**
		 * @brief �ړ�
		 *
		 * @param direction	����
		 * @param force �������
		 */
		void Move(const Vec3& direction, float force);

		/**
		 * @brief �u�ԓI�ɗ͂�������
		 *
		 * @param force �������
		 */
		void Impact(const Vec3& force);

		/**
		 * @brief �u�ԓI�ɗ͂�������
		 *
		 * @param direction ����
		 * @param force �������
		 */
		void Impact(const Vec3& direction, float force);

		/**
		 * @brief ���݂̑��x���擾
		 *
		 * @return ���݂̑��x
		 */
		Vec3 GetVelocity() {
			return m_velocity;
		}

		/**
		 * @brief ���x��0�ɂ���
		 */
		void SetVelocityZero() {
			m_velocity = Vec3(0);
		}

		/**
		 * @brief Y�����̑��x��0�ɂ���
		 */
		void SetVelocityYZero() {
			m_velocity.y = 0;
		}

		void SetTimeScale(float scale) {
			m_timeScale = scale;
		}
	};
}
