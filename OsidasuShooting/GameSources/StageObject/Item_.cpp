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
				stayTime -= deltaTime;//�@���܂鎞��
				return;
			}
			//���܂邪���Ԃ��I�������_�ł��n�܂�܂�

			auto drawComp = GetComponent<PNTStaticDraw>();

			//�_�ł̏���
			if (blinkTimeChecker == blinkTime)
			{
				blinking->SetFadeInOutTime(fadeInTime, fadeOutTime, blinkTime);
			}
			//�_�ł̏���..�I��

			//�@�_�ł̎��Ԃ��I������畨�̂�������
			blinkTime -= deltaTime;
			if (blinkTime < 0)
			{
				GetStage()->RemoveGameObject<Blinking>(blinking);
				GetStage()->RemoveGameObject<Item>(GetThis<Item>());
			}
		}
	}
}