#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class CurrentFirst :public BaseUI {
		shared_ptr<BattlePlayersUIs> m_uiObj;
	public:
		CurrentFirst(const shared_ptr<Stage>& stage)
			:BaseUI(stage, TransformData())
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
