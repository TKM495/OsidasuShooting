/*!
@file   PlayerManager.h
@brief  �v���C���[���Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"

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
	class PlayerBase;

	class PlayerManager {
#pragma region  Singleton
	private:
		// �J�X�^���폜�q�B�C���X�^���X�̍폜�͂�������̂ݍs�Ȃ��B
		struct Deleter {
			void operator()(PlayerManager const* const p) const {
				delete p;
			}
		};
		// std::unique_ptr �͍폜�q���w��o����
		static unique_ptr<PlayerManager, Deleter> m_instance;

		PlayerManager() {}
		~PlayerManager() {}
	public:
		/**
		 * @brief �C���X�^���X�̎擾�i�K�v������ΐ�������j
		 *
		 * @return �C���X�^���X
		 */
		static unique_ptr<PlayerManager, Deleter>& GetInstance() {
			if (!m_instance) {
				m_instance.reset(new PlayerManager);
			}
			return m_instance;
		}
		/**
		 * @brief �C���X�^���X�̋����폜
		 */
		static void DeleteInstance() {
			if (m_instance.get()) {
				m_instance.reset();
			}
		}
#pragma endregion

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
