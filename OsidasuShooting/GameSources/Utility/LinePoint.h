#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class LinePoint :public AdvancedGameObject {
		// 色
		Col4 m_color;
	public:
		LinePoint(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage), m_color(1.0f)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		/**
		 * @brief 色を設定
		 *
		 * @param color 色
		 */
		void SetColor(const Col4& color);
	};
}
