#pragma once
#include "stdafx.h"

namespace basecross {

	class ShackingCamera : public GameObject
	{
		shared_ptr<Camera> camera;

		Vec3 originalEye;
		Vec3 originalAt;

		Vec3 eye;
		Vec3 at;

		int shackingCount = 1;
		int curShackingCount = 1;

		Vec3 min = Vec3(-1.0f, 0.0f, 0.0f);
		Vec3 max = Vec3(1.0f, 0.0f, 0.0f);

		bool isMin = false;
		bool isMax = false;
		bool isOri = false;

		float speed = 20.0f;
		float speedincrease = 50.0f; // speed will be increased by 10%

		void ShackingLeftRight(float deltaTime);



	public:
		ShackingCamera(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		~ShackingCamera(){}
		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};

}
