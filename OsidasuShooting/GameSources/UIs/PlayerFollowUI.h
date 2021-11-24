#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class PlayerFollowUI :public BaseUI {
		shared_ptr<PlayerBase> m_owner;
		vector<shared_ptr<BaseUI>> m_uiObjects;
		Vec3 m_offset;
	public:
		PlayerFollowUI(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_owner(player),
			m_offset(Vec3(0.0f, 50.0f, 0.0f))
		{
			SetTransformInit(false);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
