#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "BaseUI.h"

namespace basecross {
	class EnergyGauge :public BaseUI {
		shared_ptr<PlayerBase> m_player;
		wstring m_textureKey;
	public:
		EnergyGauge(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_player(player),
			m_textureKey(L"BarGauge")
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
