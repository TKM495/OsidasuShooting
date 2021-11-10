/*!
@file   Fade.h
@brief  �t�F�[�h�C���A�A�E�g
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade :public GameObject {
		// �t�F�[�h�̏��(�񋓌^)
		enum class FadeState {
			Active,	// ���쒆
			Stop	// ��~��
		};
		// �t�F�[�h�̏��
		FadeState m_state;
		// �t�F�[�h�̕���(�t�F�[�h�C���Ȃ�-1,�A�E�g�Ȃ�1)
		int m_key;
		// �t�F�[�h�ɂ����鎞��
		float m_fadeTime;
		// ���Ԍv���p
		float m_delta;
		// �t�F�[�h�Ɏg�p����F
		Col4 m_color;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W
		 */
		Fade(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_state(FadeState::Stop),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_key(0),
			m_color(Col4(0.0f, 0.0f, 0.0f, 1.0f))
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		/**
		 * @brief �t�F�[�h�C���J�n
		 */
		void FadeIn();
		/**
		 * @brief �t�F�[�h�A�E�g�J�n
		 */
		void FadeOut();

		/**
		 * @brief �t�F�[�h�܂ł̎��Ԑݒ�
		 *
		 * @param time ����
		 */
		void SetFadeTime(float time) {
			m_fadeTime = time;
		}
		/**
		 * @brief �t�F�[�h�܂ł̎��Ԏ擾
		 *
		 * @return �t�F�[�h�܂ł̎���
		 */
		float GetFadeTime() {
			return m_fadeTime;
		}
		/**
		 * @brief �t�F�[�h���̐F�̐ݒ�
		 *
		 * @param color �F
		 */
		void SetFadeColor(Col4 color) {
			m_color = color;
		}
		/**
		 * @brief �t�F�[�h���̐F�̎擾
		 *
		 * @return �t�F�[�h���̐F
		 */
		Col4 GetFadeColor() {
			return m_color;
		}

		/**
		 * @brief ����t���O
		 *
		 * @return ���삵�Ă����true/��~���Ă���Ƃ���false
		 */
		bool GetFadeActive() {
			return m_state == FadeState::Active;
		}
	};

}
//end basecross
