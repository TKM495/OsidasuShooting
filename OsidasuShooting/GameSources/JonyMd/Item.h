#pragma once
#include "stdafx.h"

namespace basecross {

	class Item : public GameObject
	{
		shared_ptr<Blinking> blinking;


		// (��莞��)�b�Ƃ��ĕ\������Ă��܂��B
		float stayTime = 3.0f;//�@���̂̔��܂鎞��

		//�_�ŗp
		//�S�@�����@�͕b�Ƃ��ĕ\������Ă��܂��B
		float blinkTime = 3.0f;//�@���̂̓_�ł��鎞��
		float blinkTimeChecker = blinkTime;//�@���̂̓_�ł��鎞��

		float fadeInTime = 0.05f;
		float fadeOutTime = 0.10f;

		//�_�ŗp..�I��

	public:
		Item(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;


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
