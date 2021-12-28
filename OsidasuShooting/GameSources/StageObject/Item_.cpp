//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace modifiedClass {
		void Item::OnCreate()
		{
			auto drawComp = AddComponent<BcPNTStaticDraw>();
			drawComp->SetMeshResource(L"DEFAULT_CAPSULE");

			switch (spawnItem)
			{
			case ItemType::Bomb:
				drawComp->SetDiffuse(Col4(0.5f));
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
			shadowComp->SetMeshResource(L"DEFAULT_CAPSULE");
		}
	}
}