#pragma once
#include "stdafx.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		// ビューの作成
		void CreateViewLight();
	public:
		CharacterSelectStage() :Stage() {}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};
}
