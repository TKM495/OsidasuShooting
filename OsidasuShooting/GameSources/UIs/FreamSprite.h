
/*!
@file FreamSprite.h
@brief �g�X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FreamSprite : public GameObject {
		wstring m_textureKey;

	public:
		FreamSprite(
			const shared_ptr<Stage>& stage,
			const wstring& TextureKey
		) :
			GameObject(stage),
			m_textureKey(TextureKey)
		{}

		virtual ~FreamSprite() {};

		void OnCreate() override;
		void OnUpdate() {};
	};

}