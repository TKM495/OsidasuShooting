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
			//Random,
			totalItems // do not delete , used for randomly get above value
		};
		class Item : public GameObject
		{
			ItemType spawnItem;
			bool m_isRandom;
		public:
			Item(const shared_ptr<Stage>& stage, ItemType type, bool isRandom)
				:GameObject(stage), spawnItem(type), m_isRandom(false)
			{}

			void OnCreate() override;

			ItemType GetItemType()
			{
				return spawnItem;
			}
		};
	}
}