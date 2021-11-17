#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class LinePoint :public AdvancedGameObject {
	public:
		LinePoint(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
	};
}
