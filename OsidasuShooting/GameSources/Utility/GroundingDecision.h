/*!
@file   GroundingDecision.h
@brief  �ڒn����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GroundingDecision {
		// �I�u�W�F�N�g�̔��a
		float m_radius;
		// �������l
		static float m_threshold;
		// ������������
		bool m_isInit;
	public:
		// �R���X�g���N�^
		GroundingDecision();
		GroundingDecision(float radius);
		GroundingDecision(const Vec3& scale);

		/**
		 * @brief ����
		 *
		 * @param pos ���g�̈ʒu
		 * @return true�Ȃ�ڒn���Ă���
		 */
		bool Calculate(const Vec3& pos);

		/**
		 * @brief ���g�̔��a�̐ݒ�
		 *
		 * @param radius ���a
		 */
		void SetRadius(float radius) {
			m_radius = radius;
			m_isInit = true;
		}
		/**
		 * @brief ���g�̔��a�̐ݒ�
		 *
		 * @param scale ���g�̃X�P�[��
		 */
		void SetRadius(const Vec3& scale) {
			m_radius = scale.y / 2.0f;
			m_isInit = true;
		}
	};
}
