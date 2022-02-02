#pragma once
#include "stdafx.h"

namespace basecross {

	class Item : public GameObject
	{

		GroundingDecision m_groundingDecision;
		float rotationProcess = 0;
		float timePerRotation;
		bool doRotation = false;
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
		Item(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& Other);
	};

}
