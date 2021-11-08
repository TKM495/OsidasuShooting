#pragma once
#include "stdafx.h"

namespace basecross {

	class Obstacles2 : public GameObject
	{
	public:
		Obstacles2(const shared_ptr <Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
	};

}