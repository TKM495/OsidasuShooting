#pragma once
#include "stdafx.h"

namespace basecross {
	class Confetti :public AdvancedGameObject {
	public:
		Confetti(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		void OnDestroy()override;
	};
}
