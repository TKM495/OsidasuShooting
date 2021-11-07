/*!
@file   SatoStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SatoStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		SatoStage() :Stage() {}
		virtual ~SatoStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
	};
}
