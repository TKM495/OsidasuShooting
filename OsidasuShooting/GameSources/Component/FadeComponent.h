/*!
@file   FadeComponent.h
@brief  �t�F�[�h�R���|�[�l���g
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	class FadeComponent :public Component {
		// �t�F�[�h�̕���
		enum class Direction {
			FadeIn,
			FadeOut
		};
		// �t�F�[�h�̕���
		Direction m_dir;
		// �t�F�[�h�����쒆���ǂ���
		bool m_bActive;
		// �t�F�[�h�ɂ����鎞��
		float m_fadeTime;
		// ���Ԍv���p
		float m_delta;
		float m_maxAlpha;
		float m_minAlpha;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param objPtr �I�u�W�F�N�g�|�C���^
		 */
		FadeComponent(const shared_ptr<GameObject>& objPtr)
			:Component(objPtr),
			m_dir(Direction::FadeIn),
			m_bActive(false),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_maxAlpha(1),
			m_minAlpha(0)
		{}
		virtual void OnUpdate()override;
		virtual void OnDraw()override {}

		/**
		 * @brief �t�F�[�h���̃A���t�@�͈̔�
		 *
		 * @param max �ő�
		 * @param min �ŏ�
		 */
		void SetFadeRange(float max, float min) {
			m_maxAlpha = max;
			m_minAlpha = min;
		}

		/**
		 * @brief �t�F�[�h�C��
		 */
		void FadeIn();

		/**
		 * @brief �t�F�[�h�A�E�g
		 */
		void FadeOut();

		/**
		 * @brief �t�F�[�h�����܂ł̎��Ԑݒ�
		 *
		 * @param time ����(�b)
		 */
		void SetFadeTime(float time) {
			m_fadeTime = time;
		}

		/**
		 * @brief �t�F�[�h�����܂ł̎��Ԏ擾
		 *
		 * @return �t�F�[�h�����܂ł̎���
		 */
		float GetFadeTime() {
			return m_fadeTime;
		}

		/**
		 * @brief ���삵�Ă��邩�̃t���O
		 *
		 * @return ���쒆:true/��~��:false
		 */
		bool IsFadeActive() {
			return m_bActive;
		}
	};
}
//end basecross
