#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class ArmorGauge :public GameObject {
		TimeCounter m_testTimer;
		shared_ptr<PlayerBase> m_player;
	public:
		ArmorGauge(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player)
			:GameObject(stage), m_testTimer(5.0f), m_player(player)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
