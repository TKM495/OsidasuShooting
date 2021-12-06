/*!
@file   PlayerManager.h
@brief  �v���C���[���Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	/**
	 * @brief �v���C���[�i���o�[
	 */
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	// ���ꂪ�Ȃ��ƂȂ����G���[���o��
	// �ǋL�F�w�b�_�[���z�Q�Ƃ��Ă���̂ł��ꂪ�Ȃ��ƃG���[�ɂȂ���ۂ�
	class PlayerBase;

	class PlayerManager :public BaseSingleton<PlayerManager> {
	private: // �V���O���g���֌W
		PlayerManager() :BaseSingleton() {}
		~PlayerManager() {}
		friend class BaseSingleton<PlayerManager>;
	private:
		vector<shared_ptr<PlayerBase>> m_players;
	public:
		/**
		 * @brief �v���C���[�̒ǉ�
		 *
		 * @param playerPtr �v���C���[�̃|�C���^
		 */
		void AddPlayer(const shared_ptr<PlayerBase>& playerPtr);

		/**
		 * @brief �v���C���[�̎擾
		 *
		 * @param playerNumber �擾�������v���C���[�i���o�[
		 * @return �v���C���[�̃|�C���^
		 */
		shared_ptr<PlayerBase> GetPlayer(PlayerNumber playerNumber);

		/**
		 * @brief ���ׂẴv���C���[���擾
		 *
		 * @return �v���C���[�̃|�C���^�̃x�N�^�[�z��
		 */
		vector<shared_ptr<PlayerBase>> GetAllPlayer()const {
			return m_players;
		}

		/**
		 * @brief �\�[�g���ꂽ�v���C���[�f�[�^�̔z����擾
		 *
		 * @return �|�������Ń\�[�g���ꂽ�v���C���[�̃|�C���^�̃x�N�^�[�z��
		 */
		vector<shared_ptr<PlayerBase>> GetSortedAllPlayer()const;
	};
}
