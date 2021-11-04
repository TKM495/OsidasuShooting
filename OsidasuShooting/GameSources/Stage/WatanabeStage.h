/*!
@file   WatanabeStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WatanabeStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		WatanabeStage() :Stage() {}
		virtual ~WatanabeStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
	};
}
