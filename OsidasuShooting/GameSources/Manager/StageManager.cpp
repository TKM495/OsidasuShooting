/*!
@file   StageManager.cpp
@brief  ステージマネージャーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 初期化
	unique_ptr<StageManager, StageManager::Deleter> StageManager::m_instance = nullptr;

	void StageManager::SetPlayerType(PlayerNumber number, PlayerType type) {
		m_playerTypeMap[number] = type;
	}
	void StageManager::SetPlayerType(int number, PlayerType type) {
		if (number < 1 || 4 < number) {
			throw BaseException(
				L"不正な値です。",
				L"if (number < 1 || 4 < number) number : " + Util::IntToWStr(number),
				L"StageManager::SetPlayerType()"
			);
		}
		SetPlayerType((PlayerNumber)(number - 1), type);
	}

	PlayerType StageManager::GetPlayerType(PlayerNumber number) {
		// データがない場合
		if (m_playerTypeMap.count(number) == 0) {
			// 暫定的にデフォルト値を返すが出来れば例外を飛ばしたい
			return PlayerType::Laser;
			//throw BaseException(
			//	L"該当データが存在しません。",
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