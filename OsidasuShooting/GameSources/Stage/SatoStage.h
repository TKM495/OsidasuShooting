/*!
@file   SatoStage.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "JonyMd/CountDown.h"

namespace basecross {
	class SatoStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		SatoStage() :Stage() {}
		virtual ~SatoStage() {}
		//‰Šú‰»

		void SetPlayer();
		virtual void OnCreate()override;

		shared_ptr<CountDown> m_timer;
	};
}
