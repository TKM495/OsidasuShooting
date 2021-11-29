#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class PlayerModel :public AdvancedGameObject {
		// オーナー
		shared_ptr<GameObject> m_owner;
	public:
		PlayerModel(const shared_ptr<Stage>& stage,
			const shared_ptr<GameObject>& gameObject,
			const TransformData& transformData)
			:AdvancedGameObject(stage), m_owner(gameObject)
		{
			m_transformData = transformData;
			m_transformData.Position.y += -0.5f;
		}
		void OnCreate()override;
	};
}
