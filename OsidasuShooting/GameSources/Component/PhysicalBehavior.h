/*!
@file   PhysicalBehavior.h
@brief  �����I�ȋ������s���R���|�[�l���g�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PhysicalBehavior :public Component {
		// ��R��
		float m_drag;
		// ���݂̑��x
		Vec3 m_velocity;
		// �������l�i�ړ����x�����̒l��菬�����ꍇ0�Ƃ݂Ȃ��j
		float m_threshold;
	public:
		// �R���X�g���N�^
		PhysicalBehavior(const shared_ptr<GameObject>& gameObjectPtr)
			:Component(gameObjectPtr),
			m_velocity(Vec3(0.0f)), m_drag(3.0f), m_threshold(0.05f)
		{}

		// �R���|�[�l���g�̐���
		void OnCreate()override {}
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
		 * @brief Drag��ݒ�
		 *
		 * @param drag �ݒ�l
		 */
		void SetDrag(float drag) {
			m_drag = drag;
		}
		/**
		 * @brief Drag���擾
		 *
		 * @return ���݂�Drag
		 */
		float GetDrag() {
			return m_drag;
		}

		/**
		 * @brief ���݂̑��x���擾
		 *
		 * @return ���݂̑��x
		 */
		float GetSpeed() {
			return m_velocity.length();
		}
	};
}
