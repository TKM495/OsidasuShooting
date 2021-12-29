/*!
@file   BackPlanet.h
@brief  îwåiÇÃòfêØ
*/

#pragma once
#include "stdafx.h"
#include "BaseUI.h"

namespace basecross {
	class BackPlanet : public BaseUI {
		wstring m_textureKey;
	public:
		BackPlanet(const shared_ptr<Stage>& stage, const wstring& textureKey,
			const TransformData& transformData = TransformData())
			:BaseUI(stage, transformData), m_textureKey(textureKey)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};
}
