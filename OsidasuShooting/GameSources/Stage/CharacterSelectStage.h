#pragma once
#include "stdafx.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		// ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		CharacterSelectStage() :Stage() {}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
