/*!
@file FreamSprite.h
@brief �g�X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FreamSprite : public GameObject {
		wstring m_textureKey;
		Vec3 m_setPosition;
		Vec3 m_setScale;
	public:
		FreamSprite(
			const shared_ptr<Stage>& stage,
			const wstring& TextureKey,
			Vec3 setPosition,
			Vec3 setScale
		) :
			GameObject(stage),
			m_textureKey(TextureKey),
			m_setPosition(setPosition),
			m_setScale(setScale)
		{}

		virtual ~FreamSprite() {};

		void OnCreate() override;
		void OnUpdate() {};
	};

}