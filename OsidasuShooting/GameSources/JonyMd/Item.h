#pragma once
#include "stdafx.h"

namespace basecross {

	class Item : public GameObject
	{

		GroundingDecision m_groundingDecision;
		float rotationProcess = 0;
		float timePerRotation;
		bool doRotation = false;
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
		Item(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& Other);
	};

}
