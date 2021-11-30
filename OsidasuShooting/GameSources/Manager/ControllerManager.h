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
		enum class Direction {
			Left,
			Right
		};

		// �v���C���[�ԍ��i�擾����R���g���[���[�ɉe���j
		PlayerNumber m_playerNumber;
		// �g���K�[�̂������l
		float m_triggerThreshold;
		/**
		 * @brief �X�e�B�b�N���擾
		 *
		 * @param direction �擾�������X�e�B�b�N
		 * @return �X�e�B�b�N�̃f�[�^�iVec2�j
		 */
		Vec2 GetStickVec(Direction direction);
		/**
		 * @brief �g���K�[���擾
		 *
		 * @param direction �擾�������g���K�[
		 * @return �g���K�[�̃f�[�^�ibool�j
		 */
		bool GetTrigger(Direction direction);
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

		bool GetRightTrigger();
		bool GetLeftTrigger();
	};
}
