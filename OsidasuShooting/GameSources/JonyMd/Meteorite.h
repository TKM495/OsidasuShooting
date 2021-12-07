#pragma once
#include "stdafx.h"

namespace basecross {

	class Meteorite : public GameObject
	{
		vector<Vec3> spawnArea; 
		Vec3 spawnScale;

			void CreatingRandomPosition();
	public:
		bool destroyMeteorite = true;
		Meteorite(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{}

		void OnCreate() override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
