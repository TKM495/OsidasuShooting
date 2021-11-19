#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "BaseUI.h"
#include "NumberSprite.h"

namespace basecross {
	class BombRemainingCount :public BaseUI {
		shared_ptr<PlayerBase> m_player;
		shared_ptr<Number> m_number;
	public:
		BombRemainingCount(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_player(player)
		{
			SetTransformInit(false);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
