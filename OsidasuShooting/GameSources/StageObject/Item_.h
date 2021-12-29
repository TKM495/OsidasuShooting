#pragma once
#include "stdafx.h"

namespace basecross {
	namespace modifiedClass {
		enum class ItemType {
			//Cube,
			//Sphere,
			Bomb,
			Energy,
			//Debuff,
			totalItems // do not delete , used for randomly get above value
		};
		class Item : public GameObject
		{
			ItemType spawnItem;

		public:
			Item(const shared_ptr<Stage>& stage, ItemType type)
				:GameObject(stage), spawnItem(type)
			{}

			void OnCreate() override;

			ItemType GetItemType()
			{
				return spawnItem;
			}
		};
	}
}