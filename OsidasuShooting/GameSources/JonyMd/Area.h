#pragma once
#include "stdafx.h"

namespace basecross {

	class Area : public GameObject
	{

	public:
		Area(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{}

		void OnCreate() override;

	};

}
