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

			// (��莞��)�b�Ƃ��ĕ\������Ă��܂��B
			float stayTime = 3.0f;//�@���̂̔��܂鎞��

			//�_�ŗp
			//�S�@�����@�͕b�Ƃ��ĕ\������Ă��܂��B
			float blinkTime = 10.0f;//�@���̂̓_�ł��鎞��
			float blinkTimeChecker = blinkTime;//�@���̂̓_�ł��鎞��

			float fadeInTime = 0.5f;
			float fadeOutTime = 0.5f;

			//�_�ŗp..�I��
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