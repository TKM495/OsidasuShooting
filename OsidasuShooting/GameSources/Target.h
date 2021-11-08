#pragma once
#include "stdafx.h"

namespace basecross {

	class Target : public GameObject
	{
		float executeTime;

	public:
		Target(const shared_ptr <Stage> & stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};

}