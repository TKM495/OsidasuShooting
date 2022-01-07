/*!
@file   StageManager.h
@brief  �X�e�[�W�}�l�[�W���[
*/

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	/**
	 * @brief �v���C���[�̃^�C�v
	 */
	enum class PlayerType {
		Laser,
		Missile,
		ThreeWay
	};
	/**
	 * @brief �Z���N�g�X�e�[�W�ł̃f�[�^���i�[���A�Q�[���X�e�[�W�փf�[�^��n�����߂̃N���X
	 */
	class StageManager :public BaseSingleton<StageManager> {
	private: //�V���O���g���֌W
		StageManager() {}
		~StageManager() {}
		friend class BaseSingleton<StageManager>;
	private:
		// �v���C���[�ԍ��ɉ������v���C���[�̃^�C�v���i�[����map
		map<PlayerNumber, PlayerType> m_playerTypeMap;
		// �X�e�[�W�̔ԍ�
		int m_stageNumber;
	public:
		/**
		 * @brief �v���C���[�̃^�C�v���Z�b�g
		 *
		 * @param number �v���C���[�̔ԍ�
		 * @param type �v���C���[�̃^�C�v
		 */
		void SetPlayerType(PlayerNumber number, PlayerType type);
		/**
		 * @brief �v���C���[�̃^�C�v���Z�b�g
		 *
		 * @param number �v���C���[�̔ԍ��iint 1�`4�j
		 * @param type �v���C���[�̃^�C�v
		 */
		void SetPlayerType(int number, PlayerType type);
		/**
		 * @brief �v���C���[�̃^�C�v���擾
		 *
		 * @param number �v���C�o�[�̔ԍ�
		 * @return �v���C���[�̃^�C�v
		 */
		PlayerType GetPlayerType(PlayerNumber number);
		/**
		 * @brief �X�e�[�W�ԍ��̃Z�b�g
		 *
		 * @param number �X�e�[�W�ԍ�
		 */
		void SetStageNumber(int number);
		/**
		 * @brief �X�e�[�W�ԍ��̎擾
		 *
		 * @return �X�e�[�W�ԍ�
		 */
		int GetStageNumber();
		/**
		 * @brief �f�[�^�̃��Z�b�g
		 */
		void ResetData();
	};
}
