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

			// (��莞��)�b�Ƃ��ĕ\������Ă��܂��B
			float stayTime = 10.0f;//�@���̂̔��܂鎞��

			//�_�ŗp
			//�S�@�����@�͕b�Ƃ��ĕ\������Ă��܂��B
			float blinkingTime = 3.0f;//�@���̂̓_�ł��鎞��

			float blinkFadeInTime = 0.05f;
			float blinkStayTime = 0.01f;
			float blinkFadeOutTime = 0.10f;
			float timeChecker = blinkFadeInTime + blinkStayTime; //blinkFadeOutTime�@����n�܂�
			float blinkingSpeed = 0.002f;

			void SetAdjustColor(float colorValue)
			{
				auto component = GetComponent<PNTStaticDraw>();
				Col4 color = Col4(colorValue, colorValue, colorValue, 0.0f);
				component->SetDiffuse(color);
			}
			//�_�ŗp..�I��
		public:
			Item(const shared_ptr<Stage>& stage, ItemType type, bool isRandom)
				:GameObject(stage), spawnItem(type), m_isRandom(false)
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