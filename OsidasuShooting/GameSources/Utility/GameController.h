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

	/**
	 * @brief �R���g���[���[�̃{�^��
	 */
	enum class ControllerButton {
		A, B, X, Y,
		DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
		START, BACK,
		LEFT_THUMB, RIGHT_THUMB,
		LEFT_SHOULDER, RIGHT_SHOULDER
	};

	class GameController {
		/**
		 * @brief �X�e�B�b�N�̎��
		 */
		enum class Direction {
			Left,
			Right
		};

		// �L�[�ƃo�C�u���[�V��������t���O�̃}�b�v
		// ��F��~����A�̏����ƋN������B�̏���������Ƃ�
		// B�̂��Ƃ�A�����s�����B���z��ʂ�̓�������Ȃ��̂�h��
		map<wstring, bool> m_vibrationMap;

		// �v���C���[�ԍ��i�擾����R���g���[���[�ɉe���j
		PlayerNumber m_playerNumber;

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
		 * @brief ControllerButton��萔�ɕϊ�
		 *
		 * @param button �{�^���̎��
		 * @return XINPUT_GAMEPAD�̒萔
		 */
		int GetButtonConstants(ControllerButton button);

		/**
		 * @brief �o�C�u���[�V�����̃A�N�e�B�u�i�X���b�h�p�֐��j
		 *
		 * @param key �o�C�u���[�V���������ʂ��邽�߂̃L�[
		 * @param data �o�C�u���[�V�����f�[�^
		 */
		void ActiveVibrationThread(const wstring& key, const VibrationData& data);
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
		 * @brief �{�^���̎擾
		 *
		 * @param button ���肷��{�^��
		 * @return bool
		 */
		bool GetButtons(ControllerButton button);
		/**
		 * @brief ��Ԃ��ς�������ǂ����̔��������
		 *
		 * @param button ���肷��{�^��
		 * @return bool
		 */
		bool GetNowUpdateButtons(ControllerButton button);
		/**
		 * @brief �����ꂽ�u�Ԃ𔻒肷��
		 *
		 * @param button ���肷��{�^��
		 * @return bool
		 */
		bool GetPressedButtons(ControllerButton button);
		/**
		 * @brief �����ꂽ�u�Ԃ𔻒肷��
		 *
		 * @param button ���肷��{�^��
		 * @return bool
		 */
		bool GetReleasedButtons(ControllerButton button);
		/**
		 * @brief ��O�̃{�^���̎擾
		 *
		 * @param button ���肷��{�^��
		 * @return bool
		 */
		bool GetLastButtons(ControllerButton button);

		/**
		 * @brief �o�C�u���[�V�����̃Z�b�g
		 *
		 * @param key �o�C�u���[�V���������ʂ��邽�߂̃L�[
		 * @param data �o�C�u���[�V�����f�[�^
		 */
		void SetVibration(const wstring& key, const VibrationData& data);

		/**
		 * @brief �o�C�u���[�V�����̒�~
		 *
		 * @param key �o�C�u���[�V���������ʂ��邽�߂̃L�[
		 */
		void StopVibration(const wstring& key);

		/**
		 * @brief �o�C�u���[�V�����̃��Z�b�g
		 */
		void ResetVibration();
	};
}
