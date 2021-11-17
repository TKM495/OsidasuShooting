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
		BaseUI(const shared_ptr<Stage>& stage,
			const TransformData& transData)
			:GameObject(stage),
			m_localTransData(transData),
			m_align(Align()),
			m_anchor(Anchor())
		{}

		virtual void OnPreCreate()override;

		void SetTransformData(const TransformData& data) {
			m_localTransData = data;
			ApplyTransform();
		}

		TransformData& GetTransformData() {
			return m_localTransData;
		}

		void ApplyTransform();
	};
}
