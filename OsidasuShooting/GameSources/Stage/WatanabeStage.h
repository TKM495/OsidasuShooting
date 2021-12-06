/*!
@file   WatanabeStage.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "Utility/GameController.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	class WatanabeStage : public Stage {
		GameController m_controller;
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		WatanabeStage() :Stage(), m_controller(PlayerNumber::P1) {}
		virtual ~WatanabeStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};
}
