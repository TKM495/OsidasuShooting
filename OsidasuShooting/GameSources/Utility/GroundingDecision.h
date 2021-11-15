/*!
@file   GroundingDecision.h
@brief  �ڒn����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GroundingDecision {
		// �I�u�W�F�N�g�̍���
		float m_height;
		// �������l
		static float m_threshold;
		// ������������
		bool m_isInit;
		// ���肩�珜�O����^�O
		vector<wstring> m_tagDoNotDecision;
	public:
		// �R���X�g���N�^
		GroundingDecision();
		GroundingDecision(float height);
		GroundingDecision(const Vec3& scale);

		/**
		 * @brief ����
		 *
		 * @param pos ���g�̈ʒu
		 * @return true�Ȃ�ڒn���Ă���
		 */
		bool Calculate(const Vec3& pos);

		/**
		 * @brief ����Ɏg�������̐ݒ�
		 *
		 * @param height ����
		 */
		void SetRadius(float height) {
			m_height = height;
			m_isInit = true;
		}
		/**
		 * @brief ���g�̔��a�̐ݒ�
		 *
		 * @param scale ���g�̃X�P�[��
		 */
		void SetRadius(const Vec3& scale) {
			m_height = scale.y;
			m_isInit = true;
		}

		/**
		 * @brief ���肩�珜�O����^�O��ǉ�
		 *
		 * @param tag �^�O
		 */
		void AddNotDecisionTag(const wstring& tag) {
			m_tagDoNotDecision.push_back(tag);
		}
	};
}
