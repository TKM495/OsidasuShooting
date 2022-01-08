#pragma once
#include "stdafx.h"

namespace basecross {

	class Blinking : public GameObject
	{
		shared_ptr<BcPNTStaticDraw> component;

		float blinkingTime;
		float timeChecker;
		float showingTime;
		float hidingTime;

		bool isBlinking = false;

	public:
		Blinking(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnUpdate() override;

		void SetComponent(shared_ptr<BcPNTStaticDraw>& componentValue)
		{
			component = componentValue;
		}

		void SetBlinkingTime(float value)
		{
			blinkingTime = value;
		}
		void SetShowTime(float value)
		{
			showingTime = value;
		}
		void SetHideTime(float value)
		{
			hidingTime = showingTime + value;
		}
		void SetIsBlinking()
		{
			timeChecker = 0;
			SetUpdateActive(true);
			isBlinking = true;
		}
	};

}
