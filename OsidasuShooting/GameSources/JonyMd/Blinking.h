#pragma once
#include "stdafx.h"

namespace basecross {

	class Blinking : public Component
	{
		//list of private variables
	private:
		bool showHideStatus = true;

		float blinkingTime;
		float timeChecker;

		bool isBlinking = false;


		// for Toggle
		bool isHideShow = false;
		bool isFadeInOut = false;
		bool isAlterSize = false;

		float togglingInTime;
		float toggleStayingTime;
		float togglingOutTime;

		//for Toggle AlterSize
		float sizeValue;
		float currentSizeValue;
		float maxSizeValue;


		//for Toggle FadeInOut
		Col4 originalColor;
		Col4 changedColor;
		float changedAlpha;
		// for Toggle...end

		//list of private variables...end

		//list of private functions
		void ProgressOfHideShow();

		void ProgressOfScaling();

		void ProgressOfFading();
		void SetAdjustColor(float colorValue);
	public:
		Blinking(const shared_ptr<GameObject>& gameObjectPtr)
			:Component(gameObjectPtr)
		{}

		//override functions
		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {}

		//list of normal functions
		void SetToggleTime(float inTime, float outTime, float blinkTime, float stayTime);
		void SetToggleTime(float inTime, float outTime, float blinkTime);

		void SetShowHide();
		bool GetShowHideStatus();

		void SetFading();
		void SetOriginalColor(Col4 color);
		Col4 GetAdjustedColor();
		float GetAdjustedAlpha();

		void SetScaling(float scaleValue, float maxScaleValue);
		Vec3 GetAdjustedScale();

		void StartBlinking();
		void StopBlinking();


	};

}
