/*!
@file   WatanabeStage2.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WatanabeStage2 : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		WatanabeStage2() :Stage() {}
		virtual ~WatanabeStage2() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		void OnUpdate()override;
	};
}
