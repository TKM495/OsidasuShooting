#pragma once
#include "stdafx.h"
#include "StageObject/StageObject.h"
#include "UIHeader.h"

namespace basecross {
	class BaseUI :public GameObject {
		TransformData m_localTransData;
		Align m_align;
		Anchor m_anchor;
	public:
		BaseUI(const shared_ptr<Stage>& stage,
			const TransformData& transData,
			const Align& align,
			const Anchor& anchor)
			:GameObject(stage),
			m_localTransData(transData),
			m_align(align),
			m_anchor(anchor)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
