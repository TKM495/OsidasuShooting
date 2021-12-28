#pragma once
#include "stdafx.h"

namespace basecross {

	class Fencing : public GameObject
	{

	public:
		Fencing(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

	};

}
