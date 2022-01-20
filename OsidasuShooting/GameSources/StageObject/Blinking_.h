#pragma once
#include "stdafx.h"

namespace basecross {
	namespace modifiedClass {
		class Blinking : public GameObject
		{
			//list of private variables
			shared_ptr<SmBaseDraw> component;

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
			void SetIsBlinking(float blinkTime);
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
			void SetComponent(shared_ptr<SmBaseDraw>& componentValue);
			void SetShowHideTime(float showTime, float hideTime, float blinkTime);
			void SetFadeInOutTime(float fadeInTime, float fadeOutTime, float blinkTime);
			shared_ptr<SmBaseDraw> GetLoanedComponent()
			{
				return component;
			}
		};
	}
}