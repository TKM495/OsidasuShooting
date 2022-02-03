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
			auto blinking = AddComponent<Blinking>();
			blinking->SetOriginalColor(drawComp->GetDiffuse());
			blinking->SetOriginalColor(Col4(1, 0, 0, 0));

			auto transform = GetComponent<Transform>();
			transform->SetScale(Vec3(2));
			m_groundingDecision.SetRadius(transform->GetScale());
			m_groundingDecision.AddNotDecisionTag(L"Item");
			timePerRotation = 5.0f; // 0 to 360 degree will be happens within the defined second

			AddTag(L"Item");
		}

		void Item::OnUpdate()
		{
			auto& app = App::GetApp();
			float deltaTime = app->GetElapsedTime();

			//Rotation
			auto transform = GetComponent<Transform>();
			if (false)
			{
				float maxDegree = 360.0f;
				float minDegree = 0.0f;

				rotationProcess += deltaTime;

				float rotationY;
				if (rotationProcess > timePerRotation)
				{
					rotationY = maxDegree;
					rotationProcess = minDegree;
				}
				else
				{
					rotationY = rotationProcess * maxDegree / timePerRotation; // result is minDegree to maxDegree within the time
				}
				rotationY = XMConvertToRadians(rotationY);

				transform->SetRotation(Vec3(0.0f, rotationY, 0.0f));
			}
			//Rotation...end

			auto blinking = GetComponent<Blinking>();
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
				GetStage()->RemoveGameObject<Item>(GetThis<Item>());
			}

			Col4 color = blinking->GetAdjustedColor();
			auto drawComp = GetComponent<PNTStaticModelDraw>();
			drawComp->SetDiffuse(color);
		}

		void Item::OnDestroy()
		{
		}
	}
}