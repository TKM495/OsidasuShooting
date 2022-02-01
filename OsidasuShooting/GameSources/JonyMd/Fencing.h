#pragma once
#include "stdafx.h"

namespace basecross {

	class Fencing : public GameObject
	{
		enum Status {
			Showing,
			BlinkingToHide,
			Hiding,
			BlinkingToShow,
		};

		Status status = Fencing::Status::Showing;
		float blinkingTime;
		float blinkShowTime;
		float blinkHideTime;

		float showTime;
		float hideTime;

		float timeChecker = 0.0f;

	public:
		Fencing(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};

}
