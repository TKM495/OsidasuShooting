//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Item::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transform = GetComponent<Transform>();

		auto gravity = AddComponent<Gravity>();
		auto collision = AddComponent<CollisionObb>();

		auto stage = GetStage();
		blinking = stage->AddGameObject<Blinking>();
		blinking->SetOriginalColor(drawComp->GetDiffuse());
		blinking->SetOriginalColor(Col4(1,0,0,0));

	}



	void Item::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		if (stayTime > 0)
		{
			stayTime -= deltaTime;//　泊まる時間
			return;
		}
		//泊まるが時間が終わったら点滅が始まります


		auto drawComp = GetComponent<BcPNTStaticDraw>();

		//点滅の処理
		if (blinkTimeChecker == blinkTime)
		{
			blinking->SetFadeInOutTime(fadeInTime, fadeOutTime, blinkTime);			
		}
		//点滅の処理..終了


		//　点滅の時間が終わったら物体が消える
		blinkTime -= deltaTime;
		if (blinkTime < 0)
		{
			GetStage()->RemoveGameObject<Blinking>(blinking);
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}


		Col4 color = blinking->GetAdjustedColor();
		drawComp->SetDiffuse(color);


	}
}
