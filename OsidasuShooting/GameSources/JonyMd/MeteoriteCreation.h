#pragma once
#include "stdafx.h"

namespace basecross {

	class MeteoriteCreation : public GameObject
	{
		shared_ptr<Camera> camera;

		Vec3 originalEye;
		Vec3 originalAt;


	public:
		MeteoriteCreation(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{}

		void OnCreate() override;
		void Spawn();


		Vec3 GetCameraEye()
		{
			return originalEye;
		}

		Vec3 GetCameraAt()
		{
			return originalAt;
		}


	};

}

