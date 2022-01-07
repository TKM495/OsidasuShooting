#pragma once
#include "stdafx.h"

namespace basecross {

	class Item : public GameObject
	{
		// (一定時間)秒として表示されています。
		float stayTime = 3.0f;//　物体の泊まる時間

		//点滅用
		//全　数字　は秒として表示されています。
		float blinkingTime = 3.0f;//　物体の点滅する時間

		float blinkFadeInTime = 0.05f;
		float blinkStayTime = 0.01f;
		float blinkFadeOutTime = 0.10f;
		float timeChecker = blinkFadeInTime + blinkStayTime; //blinkFadeOutTime　から始まる	
		float blinkingSpeed = 0.002f;

		void SetAdjustColor(float colorValue)
		{
			auto component = GetComponent<BcPNTStaticDraw>();
			Col4 color = Col4(colorValue, colorValue, colorValue, 0.0f);
			component->SetDiffuse(color);
		}
		//点滅用..終了

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
