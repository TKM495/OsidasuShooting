#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class PlayerInfo :public BaseUI {
		shared_ptr<PlayerBase> m_owner;
		vector<shared_ptr<BaseUI>> m_uiObjects;
		int m_lastKillCount;
		void ItemGet(modifiedClass::ItemType type);
		void AddBombForRemain30(int num);
	public:
		PlayerInfo(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_owner(player), m_lastKillCount(0)
		{
			SetTransformInit(false);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
