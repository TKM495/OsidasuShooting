/*!
@file   JONYMDStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class JONYMDStage : public Stage {

		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		JONYMDStage() :Stage() {}
		virtual ~JONYMDStage() {}
		//‰Šú‰»
		void OnCreate() override;
		void OnUpdate() override;
		void CreateStageArea();

	};
}
