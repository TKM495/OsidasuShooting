/*!
@file FreamSprite.h
@brief 枠スプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FreamSprite : public GameObject {
		wstring m_textureKey;
		Vec3 m_setPosition;
		float m_varScale;
	public:
		FreamSprite(
			const shared_ptr<Stage>& stage,
			const wstring& TextureKey,
			Vec3 setPosition,
			float varScale
		) :
			GameObject(stage),
			m_textureKey(TextureKey),
			m_setPosition(setPosition),
			m_varScale(varScale)
		{}

		virtual ~FreamSprite() {};

		void OnCreate() override;
		void OnUpdate() {};
	};

}