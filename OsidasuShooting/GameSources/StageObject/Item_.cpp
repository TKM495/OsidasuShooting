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
			//auto transform = GetComponent<Transform>();

			auto gravity = AddComponent<Gravity>();
			auto collision = AddComponent<CollisionObb>();

			auto shadowComp = AddComponent<Shadowmap>();
			shadowComp->SetMeshResource(L"DEFAULT_CUBE");
		}
	}
}