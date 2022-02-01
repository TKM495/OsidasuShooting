#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class CurrentRank :public BaseUI {
		int m_index;
		shared_ptr<BattlePlayersUIs> m_uiObj;
	public:
		CurrentRank(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& data)
			:BaseUI(stage, data), m_index((int)player->GetPlayerNumber())
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
