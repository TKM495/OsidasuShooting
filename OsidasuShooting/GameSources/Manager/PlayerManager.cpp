/*!
@file   PlayerManager.cpp
@brief  プレイヤーを管理するクラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	unique_ptr<PlayerManager, PlayerManager::Deleter> PlayerManager::m_instance = nullptr;

	void PlayerManager::AddPlayer(const shared_ptr<PlayerBase>& playerPtr) {
		// プレイヤーのポインタを格納
		m_players.push_back(playerPtr);
	}

	shared_ptr<PlayerBase> PlayerManager::GetPlayer(PlayerNumber playerNumber) {
		for (const auto& player : m_players) {
			if (player->GetPlayerNumber() == playerNumber)
				return player;
		}

		throw BaseException(
			L"該当するプレイヤーのデータが見つかりません",
			L"playerNumber is NotFound",
			L"PlayerManager::GetPlayer()"
		);
	}

	vector<shared_ptr<PlayerBase>> PlayerManager::GetSortedAllPlayer()const {
		auto players = m_players;
		stable_sort(players.begin(), players.end(),
			[](const shared_ptr<PlayerBase>& x, const shared_ptr<PlayerBase>& y) {
				return x->GetCountKilledPlayer() > y->GetCountKilledPlayer();
			}
		);
		return players;
	}
}