#pragma once
#include "stdafx.h"

namespace basecross {

	class Obstacles : public GameObject
	{
	public:
		float check = 1.0f;
		Obstacles(const shared_ptr <Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
	};

}