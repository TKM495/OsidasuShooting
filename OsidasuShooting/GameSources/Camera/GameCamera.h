/*!
@file GameCamera.h
@brief �Q�[���J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameCamera :public Camera {
		/**
		 * @brief �X�e�[�g
		 */
		enum class State {
			Init,	// ������
			Update,	// �X�V
		};
		// At����ɂ���Eye�̈ʒu
		Vec3 m_defaultLocalEye;
		// ������At�̈ʒu
		Vec3 m_defaultAt;
		// �Ǐ]���x
		float m_followUpVelocity;
		// ���݂̃X�e�[�g
		State m_state;
		// ����������
		void Init();
		// �X�V����
		void Update();
		/**
		 * @brief At��Eye��ݒ�
		 *
		 * @param at At�̈ʒu
		 */
		void SetAtAndEye(const Vec3& at);
		/**
		 * @brief ���S�_���擾
		 *
		 * @return �v���C���[�̒��S�_
		 */
		Vec3 GetCenterPoint();
	public:
		GameCamera();

		void OnCreate() override;
		void OnUpdate() override;
	};
}

//end basecross
