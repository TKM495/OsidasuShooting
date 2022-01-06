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



		//点滅の処理
		blinkingTime -= deltaTime;
		timeChecker += deltaTime;
		float colorAdjustment;

		if (timeChecker < blinkFadeInTime)
		{
			colorAdjustment = timeChecker / blinkFadeInTime;
		}
		else if (timeChecker < (blinkFadeInTime + blinkStayTime))
		{
			colorAdjustment = 1.0f;
		}
		else if (timeChecker < (blinkFadeInTime + blinkStayTime + blinkFadeOutTime))
		{
			colorAdjustment = 1.0f - (timeChecker - (blinkFadeInTime + blinkStayTime)) / blinkFadeOutTime;
		}
		else
		{
			timeChecker = 0;
			colorAdjustment = 0.0f;

			// 毎回点滅が終わったら点滅の速度が増える
			blinkingSpeed += 0.0001f;
			blinkFadeInTime -= blinkingSpeed;
			blinkFadeOutTime -= blinkingSpeed;

			if (blinkFadeInTime < 0)
			{
				blinkFadeInTime = blinkingSpeed;
			}
			if (blinkFadeOutTime < 0)
			{
				blinkFadeOutTime = blinkingSpeed;
			}
			// 毎回点滅が終わったら点滅の速度が増える..終了
		}

		SetAdjustColor(colorAdjustment);
		//点滅の処理..終了


		//　点滅の時間が終わったら物体が消える
		if (blinkingTime < 0)
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}



	}
}
