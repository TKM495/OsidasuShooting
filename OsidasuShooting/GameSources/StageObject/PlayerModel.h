#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class PlayerModel :public AdvancedGameObject {
		// オーナー
		shared_ptr<PlayerBase> m_owner;
		// オフセット位置
		Vec3 m_offsetPos;
	public:
		PlayerModel(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& gameObject,
			const TransformData& transformData)
			:AdvancedGameObject(stage), m_owner(gameObject),
			m_offsetPos(Vec3(0.0f))
		{
			m_transformData = transformData;
			m_offsetPos.y += -0.5f * m_transformData.Scale.y;
		}
		void OnCreate()override;
		void OnUpdate()override;
	};
}
