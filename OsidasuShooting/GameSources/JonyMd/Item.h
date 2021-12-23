#pragma once
#include "stdafx.h"

namespace basecross {

	class Item : public GameObject
	{

	public:
		Item(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;


		enum class ItemType {
			Cube,
			Sphere,
			//Bomb,
			//Energy,
			//Debuff,
			totalItems // do not delete , used for randomly get above value
		};
		ItemType spawnItem;

		ItemType GetItemType()
		{
			return spawnItem;
		}
	};

}
