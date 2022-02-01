#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CurrentRank::OnCreate() {
		m_uiObj = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"RRUIs", 0, Vec3(0));
		m_uiObj->GetTransform()->SetParent(GetThis<CurrentRank>());
	}

	void CurrentRank::OnUpdate() {
		auto players = PlayerManager::GetInstance()->GetSortedAllPlayer();
		int index = 0;
		for (auto player : players) {
			if ((int)player->GetPlayerNumber() == m_index) {
				break;
			}
			index++;
		}
		m_uiObj->PlayersIconUICreate(index);
		m_uiObj->GetTransform()->SetScale(Vec3(0.3f));
		m_uiObj->GetTransform()->SetPosition(Vec3(-38.0f, 107.0f, 0.0f));
	}
	void CurrentRank::OnDraw() {
		m_uiObj->OnDraw();
	}
}