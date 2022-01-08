#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Fencing::OnCreate()
	{
		blinkingTime = 3.0f;
		blinkShowTime = 0.1f;
		blinkHideTime = 0.3f;

		showTime = 1.0f;
		hideTime = 1.0f;
		auto component = AddComponent<BcPNTStaticDraw>();
		component->SetMeshResource(L"DEFAULT_CUBE");

		auto stage = GetStage();
		auto blinking = stage->AddGameObject<Blinking>();
		stage->SetSharedGameObject(L"BlinkForFencing", blinking);
		blinking->SetComponent(component);
	}

	void Fencing::OnUpdate()
	{
		
		auto& app = App::GetApp();
		auto deltaTime = app->GetElapsedTime();

		timeChecker -= deltaTime;


		if (timeChecker > 0)
		{
			return;
		}

		auto blinking = GetStage()->GetSharedGameObject<Blinking>(L"BlinkForFencing");


		switch (status)
		{
		case Fencing::Status::Showing:
			timeChecker = showTime;
			status = Fencing::Status::BlinkingToHide;
			SetDrawActive(true); 
			break;
		case Fencing::Status::BlinkingToHide:
			blinking->SetShowTime(blinkShowTime);
			blinking->SetHideTime(blinkHideTime);
			blinking->SetBlinkingTime(blinkingTime);
			blinking->SetIsBlinking();

			timeChecker = blinkingTime;
			status = Fencing::Status::Hiding;

			break;
		case Fencing::Status::Hiding:
			timeChecker = hideTime;
			status = Fencing::Status::BlinkingToShow;
			SetDrawActive(false);
			break;
		case Fencing::Status::BlinkingToShow:
			SetDrawActive(true);

			//swap purposes
			blinking->SetShowTime(blinkHideTime);
			blinking->SetHideTime(blinkShowTime);
			//swap purposes...end
			blinking->SetBlinkingTime(blinkingTime);
			blinking->SetIsBlinking();

			timeChecker = blinkingTime;
			status = Fencing::Status::Showing;
			break;
		default:
			break;
		}
	}
}
