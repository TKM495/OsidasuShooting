/*!
@file   StageManager.cpp
@brief  �X�e�[�W�}�l�[�W���[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// ������
	unique_ptr<StageManager, StageManager::Deleter> StageManager::m_instance = nullptr;

	void StageManager::SetPlayerType(PlayerNumber number, PlayerType type) {
		m_playerTypeMap[number] = type;
	}
	void StageManager::SetPlayerType(int number, PlayerType type) {
		if (number < 1 || 4 < number) {
			throw BaseException(
				L"�s���Ȓl�ł��B",
				L"if (number < 1 || 4 < number) number : " + Util::IntToWStr(number),
				L"StageManager::SetPlayerType()"
			);
		}
		SetPlayerType((PlayerNumber)(number - 1), type);
	}

	PlayerType StageManager::GetPlayerType(PlayerNumber number) {
		// �f�[�^���Ȃ��ꍇ
		if (m_playerTypeMap.count(number) == 0) {
			// �b��I�Ƀf�t�H���g�l��Ԃ����o����Η�O���΂�����
			return PlayerType::Laser;
			//throw BaseException(
			//	L"�Y���f�[�^�����݂��܂���B",
			//	L"if (m_playerTypeMap.count(number) == 0) number : " + Util::IntToWStr((int)number),
			//	L"StageManager::GetPlayerType()"
			//);
		}
		return m_playerTypeMap[number];
	}

	void StageManager::SetStageNumber(int number) {
		m_stageNumber = number;
	}

	int StageManager::GetStageNumber() {
		return m_stageNumber;
	}

	void StageManager::ResetData() {
		m_stageNumber = 0;
		m_playerTypeMap.clear();
	}
}