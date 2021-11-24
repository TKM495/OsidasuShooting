#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class SimpleSprite :public BaseUI {
		wstring m_textureKey;
	public:
		SimpleSprite(const shared_ptr<Stage>& stage, const wstring& textureKey,
			const TransformData& transformData = TransformData())
			:BaseUI(stage, transformData), m_textureKey(textureKey)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
