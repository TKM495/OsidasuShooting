//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace modifiedClass {
		void Item::OnCreate()
		{
			auto drawComp = AddComponent<PNTStaticModelDraw>();
			drawComp->SetOwnShadowActive(true);

			//auto shadowComp = AddComponent<Shadowmap>();
			AddComponent<CircleShadow>(1.0f);
			switch (spawnItem)
			{
			case ItemType::Bomb:
				drawComp->SetMeshResource(L"BombItemModel");
				//shadowComp->SetMeshResource(L"BombItemModel");
				break;
			case ItemType::Energy:
				drawComp->SetMeshResource(L"EnergyItemModel");
				//shadowComp->SetMeshResource(L"EnergyItemModel");
				break;
			case ItemType::totalItems:
				break;
			default:
				break;
			}

			auto collComp = AddComponent<CollisionObb>();
			//collComp->SetDrawActive(true);

			auto gravity = AddComponent<Gravity>();

			AddComponent<PhysicalBehavior>();

			auto stage = GetStage();
			blinking = stage->AddGameObject<Blinking>();
			blinking->SetOriginalColor(drawComp->GetDiffuse());
			blinking->SetOriginalColor(Col4(1, 0, 0, 0));

			GetComponent<Transform>()->SetScale(Vec3(2));
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
			if (blinkTimeChecker == blinkTime)
			{
				blinking->SetToggleTime(fadeInTime, fadeOutTime, blinkTime);
				blinking->SetFading();
				blinking->StartBlinking();
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
			auto drawComp = GetComponent<PNTStaticModelDraw>();
			drawComp->SetDiffuse(color);
		}

		void Item::OnDestroy()
		{
			auto objs = GetStage()->GetGameObjectVec();

			for (auto obj : objs)
			{
				auto blinkingObj = dynamic_pointer_cast<Blinking>(obj);
				if (blinkingObj == blinking)
				{
					GetStage()->RemoveGameObject<Blinking>(blinking);
				}
			}
		}
	}
}