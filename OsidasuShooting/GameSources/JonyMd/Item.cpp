//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Item::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transform = GetComponent<Transform>();

		auto gravity = AddComponent<Gravity>();
		auto collision = AddComponent<CollisionObb>();

		auto blinking = AddComponent<Blinking>();
		blinking->SetOriginalColor(drawComp->GetDiffuse());
		blinking->SetOriginalColor(Col4(1,0,0,0));

		//m_groundingDecision.SetRadius(transform->GetScale());
		timePerRotation = 1.0f; // 0 to 360 degree will be happens within the defined second

	}


	void Item::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		//Rotation
		if (doRotation)
		{
			auto transform = GetComponent<Transform>();
			float maxDegree = 360.0f;
			float minDegree = 0.0f;

			rotationProcess += deltaTime;

			float rotationY;
			if (rotationProcess > timePerRotation)
			{
				rotationY = maxDegree;
				rotationProcess = minDegree;
			}else
			{
				rotationY = rotationProcess * maxDegree / timePerRotation; // result is minDegree to maxDegree within the time
			}
			rotationY = XMConvertToRadians(rotationY);

			transform->SetRotation(Vec3(0.0f, rotationY, 0.0f));
		}
		//Rotation...end

		auto blinking = GetComponent<Blinking>();
		if (stayTime > 0)
		{
			stayTime -= deltaTime;//�@���܂鎞��
			return;
		}
		//���܂邪���Ԃ��I�������_�ł��n�܂�܂�


		auto drawComp = GetComponent<BcPNTStaticDraw>();

		//�_�ł̏���
		if (blinkTimeChecker == blinkTime)
		{
			blinking->SetToggleTime(fadeInTime, fadeOutTime, blinkTime);
			blinking->SetFading();
			blinking->StartBlinking();
		}
		//�_�ł̏���..�I��


		//�@�_�ł̎��Ԃ��I������畨�̂�������
		blinkTime -= deltaTime;
		if (blinkTime < 0)
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}


		Col4 color = blinking->GetAdjustedColor();
		drawComp->SetDiffuse(color);



	}//OnUpdate...end

	void Item::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		doRotation = true;

	}
}
