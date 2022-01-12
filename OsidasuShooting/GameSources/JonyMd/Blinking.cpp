#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Blinking::OnUpdate()
	{

		if (!isBlinking)
		{
			if (toggle == Blinking::FadeInOut)
			{
				component->SetDiffuse(originalColor);
			}
			SetUpdateActive(false);
			return;
		}

		auto& app = App::GetApp();
		auto deltaTime = app->GetElapsedTime();

		blinkingTime -= deltaTime;
		if (blinkingTime < 0)
		{
			isBlinking = false;
			return;
		}


		timeChecker += deltaTime;

		switch (toggle)
		{
		case Blinking::HideAndShow:
			ProgressOfHideShow();
			break;
		case Blinking::FadeInOut:
			ProgressOfFadeInOut();
			break;
		default:
			break;
		}

	}


	void Blinking::SetComponent(shared_ptr<BcPNTStaticDraw>& componentValue)
	{
		component = componentValue;
	}

	void Blinking::SetIsBlinking(float blinkTime)
	{
		blinkingTime = blinkTime;
		SetUpdateActive(true);
		isBlinking = true;
	}



	void Blinking::SetShowHideTime(float showTime, float hideTime, float blinkTime)
	{
		showingTime = showTime;
		hidingTime = showingTime + hideTime;
		toggle = Blinking::Toggle::HideAndShow;
		timeChecker = 0;//showingTime　から始まる	
		SetIsBlinking(blinkTime);
	}
	
	void Blinking::SetFadeInOutTime(float fadeInTime, float fadeOutTime, float blinkTime)
	{
		fadingInTime = fadeInTime;
		fadingOutTime = fadingInTime + fadeOutTime;
		fadeInOutSpeed = 0.002f;
		fadeInOutStay = 0.01f;
		timeChecker = fadingInTime + fadeInOutStay; //fadingOutTime　から始まる	

		originalColor = component->GetDiffuse();
		toggle = Blinking::Toggle::FadeInOut;

		SetIsBlinking(blinkTime);
	}



	void Blinking::ProgressOfHideShow()
	{

		if (timeChecker < showingTime)
		{
			component->SetDrawActive(true);
		}
		else if (timeChecker < hidingTime)
		{
			component->SetDrawActive(false);
		}
		else
		{
			timeChecker = 0;

			//速度増えるため
			if (showingTime >= hidingTime - showingTime)
			{
				showingTime -= showingTime * 10 / 100;
				hidingTime -= hidingTime * 1 / 100;
			}
			else
			{
				hidingTime -= hidingTime * 10 / 100;
				showingTime -= showingTime * 1 / 100;

			}
		}
	}

	void Blinking::ProgressOfFadeInOut()
	{

		float colorAdjustment;

		if (timeChecker < fadingInTime)
		{
			colorAdjustment = timeChecker / fadingInTime;
		}
		else if (timeChecker < (fadingInTime + fadeInOutStay))
		{
			colorAdjustment = 1.0f;
		}
		else if (timeChecker < (fadingOutTime + fadeInOutStay))
		{
			colorAdjustment = 1.0f - (timeChecker - (fadingInTime + fadeInOutStay)) / fadingOutTime;
		}
		else
		{
			timeChecker = 0;
			colorAdjustment = 0.0f;
			fadeInOutSpeed += fadeInOutSpeed * 5 / 100;
			fadingInTime -= fadeInOutSpeed;
			fadingOutTime -= fadeInOutSpeed;

			if (fadingInTime < 0)
			{
				fadingInTime = fadeInOutSpeed;
			}
			if (fadingOutTime < 0)
			{
				fadingOutTime = fadeInOutSpeed;
			}
		}

		SetAdjustColor(colorAdjustment);
	}

	void Blinking::SetAdjustColor(float colorValue)
	{
		Col4 color = Col4(colorValue, colorValue, colorValue, 0.0f);
		component->SetDiffuse(color);
	}
}
