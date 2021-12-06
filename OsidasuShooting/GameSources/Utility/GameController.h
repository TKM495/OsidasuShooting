/*!
@file   GameController.h
@brief  �R���g���[���[�Ǘ��N���X
 */

#pragma once
#include "stdafx.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	/**
	 * @brief �o�C�u���[�V�����f�[�^
	 */
	struct VibrationData
	{
		float Time;				// �p������
		WORD RightMotorSpeed;	// �E���[�^�[�i0�`65535�j
		WORD LeftMotorSpeed;		// �����[�^�[�i0�`65535�j

		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param time				�p������
		 * @param rightMotorSpeed	�E���[�^�[�i0�`65535�j
		 * @param leftMotorSpeed	�����[�^�[�i0�`65535�j
		 */
		VibrationData(float time, WORD rightMotorSpeed, WORD leftMotorSpeed) {
			this->Time = time;
			this->RightMotorSpeed = rightMotorSpeed;
			this->LeftMotorSpeed = leftMotorSpeed;
		}
	};

	class GameController {
		/**
		 * @brief �X�e�B�b�N�̎��
		 */
		enum class Direction {
			Left,
			Right
		};

		// �v���C���[�ԍ��i�擾����R���g���[���[�ɉe���j
		PlayerNumber m_playerNumber;
		TimeCounter m_timer;
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
		void th(const VibrationData& data);
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param number �v���C���[�ԍ�
		 */
		GameController(PlayerNumber number);

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

		/**
		 * @brief �E�g���K�[��������Ă��邩
		 *
		 * @return true�Ȃ牟����Ă���
		 */
		bool GetRightTrigger();
		/**
		 * @brief ���g���K�[��������Ă��邩
		 *
		 * @return true�Ȃ牟����Ă���
		 */
		bool GetLeftTrigger();

		void SetVibration(const VibrationData& data);
		void ResetVibration();
	};
}
