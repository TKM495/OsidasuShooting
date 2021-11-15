/*!
@file   ControllerManager.h
@brief  �R���g���[���[�}�l�[�W���[
 */

#pragma once
#include "stdafx.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	class ControllerManager {
		/**
		 * @brief �X�e�B�b�N�̎��
		 */
		enum class Stick {
			Left,
			Right
		};

		// �v���C���[�ԍ��i�擾����R���g���[���[�ɉe���j
		PlayerNumber m_playerNumber;
		/**
		 * @brief �X�e�B�b�N���擾
		 *
		 * @param stick �擾�������X�e�B�b�N
		 * @return �X�e�B�b�N�̃f�[�^�iVec2�j
		 */
		Vec2 GetStickVec(Stick stick);
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param number �v���C���[�ԍ�
		 */
		ControllerManager(PlayerNumber number);

		/**
		 * @brief �R���g���[���[�擾
		 *
		 * @return CONTROLER_STATE
		 */
		CONTROLER_STATE GetControler();

		/**
		 * @brief ���X�e�B�b�N�̎擾
		 *
		 * @return Vec3�̃x�N�g��
		 */
		Vec3 GetLeftStickVec();

		/**
		 * @brief �E�X�e�B�b�N�̎擾
		 *
		 * @return Vec3�̃x�N�g��
		 */
		Vec3 GetRightStickVec();
	};
}
