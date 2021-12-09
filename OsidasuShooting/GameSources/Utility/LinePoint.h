#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class LinePoint :public AdvancedGameObject {
		// F
		Col4 m_color;
	public:
		LinePoint(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage), m_color(1.0f)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		/**
		 * @brief F‚ğİ’è
		 *
		 * @param color F
		 */
		void SetColor(const Col4& color);
	};
}
