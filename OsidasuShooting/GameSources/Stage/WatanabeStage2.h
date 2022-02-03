/*!
@file   WatanabeStage2.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "StageObject/Confetti.h"

namespace basecross {
	class WatanabeStage2 : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		shared_ptr<Confetti> m_confetti;
		shared_ptr<AdvancedGameObject> m_obj;
		float m_time = 0;
	public:
		//\’z‚Æ”jŠü
		WatanabeStage2() :Stage() {}
		virtual ~WatanabeStage2() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		void OnUpdate()override;
	};
}
