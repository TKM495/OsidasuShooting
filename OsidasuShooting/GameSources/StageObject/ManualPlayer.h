#pragma once
#include "stdafx.h"

namespace basecross {
	class ManualPlayer :public GameObject {
	public:
		ManualPlayer(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
