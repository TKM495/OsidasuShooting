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
		Col4 color = Col4(0.0f, 0.5f, 0.0f, 0.0f);
		component->SetDiffuse(color);

		auto transform = GetComponent<Transform>();

		Vec3 position = transform->GetPosition();
		Vec3 scale = transform->GetScale();

		position = Vec3(0,0,0);
		scale = Vec3(10,1,10);

		transform->SetPosition(position);
		transform->SetScale(scale);

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
			blinking->SetShowHideTime(blinkShowTime, blinkHideTime, blinkingTime);

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

			blinking->SetShowHideTime(blinkHideTime, blinkShowTime, blinkingTime);// showTime and hideTime has been swaped

			timeChecker = blinkingTime;
			status = Fencing::Status::Showing;
			break;
		default:
			break;
		}
	}
}
