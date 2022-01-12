#pragma once
#include "stdafx.h"
#include "StageObject/Blinking_.h"

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
			shared_ptr<modifiedClass::Blinking> blinking;

			// (��莞��)�b�Ƃ��ĕ\������Ă��܂��B
			float stayTime = 10.0f;//�@���̂̔��܂鎞��

			//�_�ŗp
			//�S�@�����@�͕b�Ƃ��ĕ\������Ă��܂��B
			float blinkTime = 3.0f;//�@���̂̓_�ł��鎞��
			float blinkTimeChecker = blinkTime;//�@���̂̓_�ł��鎞��

			float fadeInTime = 0.05f;
			float fadeOutTime = 0.10f;

			//�_�ŗp..�I��
		public:
			Item(const shared_ptr<Stage>& stage, ItemType type, bool isRandom)
				:GameObject(stage), spawnItem(type)
			{}

			void OnCreate() override;
			void OnUpdate() override;

			ItemType GetItemType()
			{
				return spawnItem;
			}
		};
	}
}