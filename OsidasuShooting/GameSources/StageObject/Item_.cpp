//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace modifiedClass {
		void Item::OnCreate()
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetMeshResource(L"DEFAULT_CUBE");

			switch (spawnItem)
			{
			case ItemType::Bomb:
				drawComp->SetTextureResource(L"BombItem");
				break;
			case ItemType::Energy:
				drawComp->SetTextureResource(L"EnergyItem");
				break;
			case ItemType::totalItems:
				break;
			default:
				break;
			}
			auto transform = GetComponent<Transform>();

			auto gravity = AddComponent<Gravity>();
			auto collision = AddComponent<CollisionObb>();

			auto shadowComp = AddComponent<Shadowmap>();
			shadowComp->SetMeshResource(L"DEFAULT_CUBE");

			AddComponent<PhysicalBehavior>();

			auto stage = GetStage();
			blinking = stage->AddGameObject<modifiedClass::Blinking>();
			blinking->SetComponent(drawComp);
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

			auto drawComp = GetComponent<PNTStaticDraw>();

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
		}
	}
}