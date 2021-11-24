#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class SimpleSprite :public GameObject {
		wstring m_textureKey;
		TransformData m_TransformData;
	public:
		SimpleSprite(const shared_ptr<Stage>& stage, const wstring& textureKey,
			const TransformData& transformData = TransformData())
			:GameObject(stage), m_textureKey(textureKey),
			m_TransformData(transformData)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
