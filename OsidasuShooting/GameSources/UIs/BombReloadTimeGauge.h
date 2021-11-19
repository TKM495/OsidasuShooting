#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class BombReloadTimeGauge :public BaseUI {
		shared_ptr<PlayerBase> m_player;
		wstring m_textureKey;
	public:
		BombReloadTimeGauge(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_player(player),
			m_textureKey(L"CircleGauge")
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
