#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class SimpleSprite :public BaseUI {
		wstring m_textureKey;
		Flt2 halfSize;
	public:
		SimpleSprite(const shared_ptr<Stage>& stage, const wstring& textureKey,
			const TransformData& transformData = TransformData())
			:BaseUI(stage, transformData), m_textureKey(textureKey)
		{}

		void OnCreate()override;

		Flt2 GetHalfSize()
		{
			return halfSize;
		}
	};

	class BoardPoly :public AdvancedGameObject {
		wstring m_textureKey;
	public:
		BoardPoly(const shared_ptr<Stage>& stage, const wstring& textureKey,
			const TransformData& transformData = TransformData())
			:AdvancedGameObject(stage), m_textureKey(textureKey)
		{
			m_transformData = transformData;
		}

		void OnCreate()override;
	};
}
