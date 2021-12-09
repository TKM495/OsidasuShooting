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
		WORD LeftMotorSpeed;	// �����[�^�[�i0�`65535�j

		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param rightMotorSpeedRate	// �E���[�^�[�̉�]���x�i0�`1�j(����])
		 * @param leftMotorSpeedRate	// �����[�^�[�̉�]���x�i0�`1�j(���])
		 * @param time					// �p������
		 */
		VibrationData(float rightMotorSpeedRate, float leftMotorSpeedRate, float time) {
			this->RightMotorSpeed = WORD(65535 * Utility::Clamp(rightMotorSpeedRate, 0.0f, 1.0f));
			this->LeftMotorSpeed = WORD(65535 * Utility::Clamp(leftMotorSpeedRate, 0.0f, 1.0f));
			this->Time = time;
		}
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param rightMotorSpeedRate	// �E���[�^�[�̉�]���x�i0�`1�j(����])
		 * @param leftMotorSpeedRate	// �����[�^�[�̉�]���x�i0�`1�j(���])
		 */
		VibrationData(float rightMotorSpeedRate, float leftMotorSpeedRate) {
			this->RightMotorSpeed = WORD(65535 * Utility::Clamp(rightMotorSpeedRate, 0.0f, 1.0f));
			this->LeftMotorSpeed = WORD(65535 * Utility::Clamp(leftMotorSpeedRate, 0.0f, 1.0f));
			this->Time = INFINITY;
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

		// �o�C�u���[�V������ON�ɂȂ��Ă��邩
		bool m_isVibrationON;
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

		/**
		 * @brief �o�C�u���[�V�����̃A�N�e�B�u�i�X���b�h�p�֐��j
		 *
		 * @param data �o�C�u���[�V�����f�[�^
		 */
		void ActiveVibrationThread(const VibrationData& data);
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param number �v���C���[�ԍ�
		 */
		GameController(PlayerNumber number);
		/**
		 * @brief �f�X�g���N�^
		 */
		~GameController();

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

		/**
		 * @brief �o�C�u���[�V�����̃Z�b�g
		 *
		 * @param data �o�C�u���[�V�����f�[�^
		 */
		void SetVibration(const VibrationData& data);

		/**
		 * @brief �o�C�u���[�V�����̃��Z�b�g
		 */
		void ResetVibration();
	};
}
