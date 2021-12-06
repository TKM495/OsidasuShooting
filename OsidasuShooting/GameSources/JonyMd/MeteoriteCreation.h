#pragma once
#include "stdafx.h"

namespace basecross {

	class MeteoriteCreation : public GameObject
	{
	public:
		MeteoriteCreation(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{}

		void Spawn();
	};

}

