#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Blinking::OnCreate()
	{
		originalColor = Col4(1.0f, 0.0f, 0.0f, 1.0f);

		togglingInTime = 0.5f;
		toggleStayingTime = 0.0f;
		togglingOutTime = togglingInTime + toggleStayingTime + 0.5f;
		blinkingTime = 10.0f;
	}

	void Blinking::OnUpdate()
	{

		if (!isBlinking)
		{
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

		if (isHideShow)
		{
			ProgressOfHideShow();
		}

		if (isFadeInOut)
		{
			ProgressOfFading();
		}

		if (isAlterSize)
		{
			ProgressOfScaling();
		}

	}

	bool Blinking::GetShowHideStatus()
	{
		return showHideStatus;
	}

	void Blinking::SetOriginalColor(Col4 color)
	{
		originalColor = color;
	}

	float Blinking::GetAdjustedAlpha()
	{
		return changedAlpha;
	}
	Col4 Blinking::GetAdjustedColor()
	{
		return changedColor;
	}
	Vec3 Blinking::GetAdjustedScale()
	{
		Vec3 scale = Vec3(currentSizeValue, currentSizeValue, currentSizeValue);
		return scale;
	}

	void Blinking::StartBlinking()
	{
		if (!isFadeInOut && isAlterSize && isHideShow)
		{
			isFadeInOut = true;// default
		}

		timeChecker = 0;

		SetUpdateActive(true);
		changedColor = originalColor;
		changedAlpha = 0.01f;
		isBlinking = true;
	}
	void Blinking::StopBlinking()
	{
		SetUpdateActive(false);
		isHideShow = false;
		isFadeInOut = false;
		isAlterSize = false;

		changedColor = originalColor;
		changedAlpha = 1.0f;

		isBlinking = false;
	}



	void Blinking::SetToggleTime(float inTime, float outTime, float blinkTime)
	{
		float stayTime = 0.0;
		SetToggleTime(inTime, outTime, blinkTime, stayTime);
	}
	void Blinking::SetToggleTime(float inTime, float outTime, float blinkTime, float stayTime)
	{
		if (stayTime < 0)
		{
			stayTime = 0.0;
		}
		togglingInTime = inTime;
		toggleStayingTime = inTime + stayTime;
		togglingOutTime = inTime + stayTime+ outTime;
		blinkingTime = blinkTime;

	}

	void Blinking::SetShowHide()
	{
		isHideShow = true;
	}
	
	void Blinking::SetFading()
	{
		isFadeInOut = true;
	}
	
	void Blinking::SetScaling(float scaleValue, float maxScaleValue)
	{
		sizeValue = scaleValue;
		maxSizeValue = maxScaleValue;

		isAlterSize = true;

		currentSizeValue = sizeValue;

	}



	void Blinking::ProgressOfHideShow()
	{

		if (timeChecker < togglingInTime)
		{
			showHideStatus = true;
		}
		else if (timeChecker < (togglingOutTime-toggleStayingTime))
		{
			showHideStatus = false;
		}
		else
		{
			timeChecker = 0;
		}
	}

	void Blinking::ProgressOfFading()
	{
		float colorAdjustment;
		if (timeChecker < togglingInTime)
		{
			colorAdjustment = 1 - (timeChecker / togglingInTime);
		}
		else if (timeChecker < toggleStayingTime)
		{
			colorAdjustment = 0.0f;
		}
		else if (timeChecker < togglingOutTime)
		{
			colorAdjustment = (timeChecker / togglingOutTime);
		}
		else
		{
			timeChecker = 0;
			colorAdjustment = 1.0f;
		}
		SetAdjustColor(colorAdjustment);
	}


	void Blinking::SetAdjustColor(float colorValue)
	{
		Col4 color = Col4(colorValue, colorValue, colorValue, 1.0f);
		
		if (originalColor.x != originalColor.y || originalColor.x != originalColor.z)
		{
			if (color.x < originalColor.x)
			{
				color.x = originalColor.x;
			}
			if (color.y < originalColor.y)
			{
				color.y = originalColor.y;
			}
			if (color.z < originalColor.z)
			{
				color.z = originalColor.z;
			}

		}
		
		changedColor = color;
		changedAlpha = colorValue;
	}


	void Blinking::ProgressOfScaling()
	{

		if (timeChecker < togglingInTime)
		{
			currentSizeValue = sizeValue + ((maxSizeValue - sizeValue) * timeChecker / togglingInTime);
		}
		else if (timeChecker < toggleStayingTime)
		{
			currentSizeValue = maxSizeValue;
		}
		else if (timeChecker < togglingOutTime)
		{
			currentSizeValue = maxSizeValue - ((maxSizeValue - sizeValue) * timeChecker / togglingOutTime);
		}
		else
		{
			timeChecker = 0;
			currentSizeValue = sizeValue;
		}

	}
}
