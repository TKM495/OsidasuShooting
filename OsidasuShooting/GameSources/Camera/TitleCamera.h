#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class TitleCamera :public AdvancedGameObject {
	public:
		TitleCamera(const shared_ptr<Stage>& stage)
			:AdvancedGameObject(stage)
		{}
		void OnCreate()override;
		void OnUpdate()override;
	};
}
