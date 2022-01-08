#include "stdafx.h"
#include "Project.h"

namespace basecross {

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

			//‘¬“x‘‚¦‚é‚½‚ß
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
}
