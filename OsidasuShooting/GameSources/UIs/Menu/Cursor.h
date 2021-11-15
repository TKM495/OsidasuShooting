/*!
@file   Cursor.h
@brief  ���j���[�J�[�\���N���X
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	class Cursor :public GameObject {
		// �F
		Col4 m_color;
		// �ő哧�ߗ�
		float m_max;
		// �ŏ����ߗ�
		float m_min;
		// ���x
		float m_rate;
		// ���Ԍv���p
		float m_delta;
		// �J�[�\���e�N�X�`��
		wstring m_name;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W
		 * @param name �J�[�\���̃e�N�X�`���̖��O
		 */
		Cursor(const shared_ptr<Stage>& stage,
			const wstring& name)
			:GameObject(stage),
			m_name(name),m_max(0.3f), m_min(0.2f), m_rate(6.0f), m_delta(0.0f)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		/**
		 * @brief ���ߗ��̐ݒ�
		 *
		 * @param max �ő哧�ߗ�
		 * @param min �ŏ����ߗ�
		 */
		void SetValue(float max, float min) {
			m_max = max;
			m_min = min;
		}

		/**
		 * @brief �_�ł̃��[�g�̐ݒ�
		 *
		 * @param rate ���[�g
		 */
		void SetRate(float rate) {
			m_rate = rate;
		}
	};

}
//end basecross
