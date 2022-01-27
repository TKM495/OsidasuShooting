#pragma once
#include "stdafx.h"
#include "JonyMd/Blinking.h"

namespace basecross {
	namespace modifiedClass {
		enum class ItemType {
			//Cube,
			//Sphere,
			Bomb,
			Energy,
			totalItems // do not delete , used for randomly get above value
		};
		class Item : public GameObject
		{
			ItemType spawnItem;
			shared_ptr<Blinking> blinking;

			// (一定時間)秒として表示されています。
			float stayTime = 3.0f;//　物体の泊まる時間

			//点滅用
			//全　数字　は秒として表示されています。
			float blinkTime = 10.0f;//　物体の点滅する時間
			float blinkTimeChecker = blinkTime;//　物体の点滅する時間

			float fadeInTime = 0.5f;
			float fadeOutTime = 0.5f;

			//点滅用..終了
		public:
			Item(const shared_ptr<Stage>& stage, ItemType type)
				:GameObject(stage), spawnItem(type)
			{}

			void OnCreate() override;
			void OnUpdate() override;
			void OnDestroy()override;

			ItemType GetItemType()
			{
				return spawnItem;
			}
		};
	}
}