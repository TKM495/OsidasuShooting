#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"
#include "UIHeader.h"

namespace basecross {
	class BaseUI :public AdvancedGameObject {
		Align m_align;
		Anchor m_anchor;
	public:
		BaseUI(const shared_ptr<Stage>& stage,
			const TransformData& transData,
			const Align& align,
			const Anchor& anchor)
			:AdvancedGameObject(stage),
			m_align(align),
			m_anchor(anchor)
		{
			m_transformData = transData;
		}
		BaseUI(const shared_ptr<Stage>& stage,
			const TransformData& transData)
			:BaseUI(stage, transData, Align(), Anchor())
		{}
		virtual void OnPreCreate()override;
	};
}
