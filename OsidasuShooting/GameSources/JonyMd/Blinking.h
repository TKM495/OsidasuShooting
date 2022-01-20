#pragma once
#include "stdafx.h"

namespace basecross {

	class Blinking : public GameObject
	{
		//list of private variables
	private:
		shared_ptr<BcPNTStaticDraw> component;

		float blinkingTime;
		float timeChecker;

		bool isBlinking = false;

		//for Toggle HideAndShow
		float showingTime;
		float hidingTime;


		//for Toggle FadeInOut
		float fadingInTime;
		float fadingOutTime;
		float fadeInOutSpeed;
		float fadeInOutStay;
		Col4 originalColor;
		Col4 changedColor;
		float changedAlpha;

		//list of private variables...end

		//private enum
		enum Toggle
		{
			HideAndShow,
			FadeInOut
		};
		Toggle toggle = Blinking::Toggle::HideAndShow;
		//private enum...end


		//list of private functions
		void StartBlinking(float blinkTime);

		void ProgressOfHideShow();

		void ProgressOfFadeInOut();
		void SetAdjustColor(float colorValue);
	public:
		Blinking(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		//override functions
		void OnUpdate() override;

		//list of normal functions
		void SetComponent(shared_ptr<BcPNTStaticDraw>& componentValue);
		void SetShowHideTime(float showTime, float hideTime, float blinkTime);

		void SetFadeInOutTime(float fadeInTime, float fadeOutTime, float blinkTime);
		void SetOriginalColor(Col4 color);
		Col4 GetAdjustedColor();
		float GetAdjustedAlpha();

		void StopBlinking();

	};

}
