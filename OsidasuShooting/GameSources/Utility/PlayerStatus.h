#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"
#include "StageObject/PlayerBase.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	/**
	 * @brief �v���C���[���ʂ̃X�e�[�^�X
	 */
	struct PlayerCommonStatus {
		float DefaultEnergy;        // �f�t�H���g�̃G�l���M�[�l
		float CorrectAngle;         // �e�̏Ə��̕␳�p�x
		float BombAimMovingDistance;// ���e�̏Ə��̈ړ���
		float BulletAimLineLength;  // �e�̏Ə����̒���
		int DefaultBombCount;       // �f�t�H���g�̔��e�̏�����
		float GravityMagnification; // �d��
	};
	/**
	 * @brief �v���C���[�ʂ̃X�e�[�^�X
	 */
	struct StatusByPlayer {
		float MoveSpeed;            // �ړ����x
		float JumpAmount;           // �W�����v��
		float EnergyUseInBulletShot;// �e�̔��˂Ɏg�p����G�l���M�[(1��������)
		float UseEnergyInHover;     // �z�o�[�ŏ����G�l���M�[(���b)
		float EnergyRecoveryAmount; // �G�l���M�[�̉񕜑��x
		float BulletPower;          // �e�̈З�
		float BombPower;            // ���e�̈З�
		float BulletRateOfFire;     // �e�̔��ˑ��x
		float BombReloadSpeed;      // ���e�̃����[�h���x
		float Weight;               // �d��
	};

	class PlayerStatus :public BaseSingleton<PlayerStatus> {
	private:
		PlayerStatus() :BaseSingleton() {
			DataExtraction();
		}
		~PlayerStatus() {}
		friend class BaseSingleton<PlayerStatus>;
	private:
		map<PlayerNumber, Col4> m_colorTable;
		PlayerCommonStatus m_commonStatus;
		map<PlayerType, StatusByPlayer> m_statusByPlayer;
		void DataExtraction();
	public:
		Col4 GetPlayerColor(PlayerNumber number);
		Col4 GetPlayerColor(int number);
		void SetPlayerData(const shared_ptr<PlayerBase>& player);
	};
}
