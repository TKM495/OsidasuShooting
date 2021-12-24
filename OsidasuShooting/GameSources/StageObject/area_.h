#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	namespace modifiedClass {
		class Area : public AdvancedGameObject
		{
		public:
			Area(const shared_ptr<Stage>& stage,
				const TransformData& data)
				:AdvancedGameObject(stage)
			{
				m_transformData = data;
			}

			void OnCreate() override;
		};
	}
}
