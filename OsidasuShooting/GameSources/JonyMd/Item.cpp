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

		auto stage = GetStage();
		blinking = stage->AddGameObject<Blinking>();
		blinking->SetOriginalColor(drawComp->GetDiffuse());
		blinking->SetOriginalColor(Col4(1,0,0,0));

	}



	void Item::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

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
			blinking->SetFadeInOutTime(fadeInTime, fadeOutTime, blinkTime);			
		}
		//�_�ł̏���..�I��


		//�@�_�ł̎��Ԃ��I������畨�̂�������
		blinkTime -= deltaTime;
		if (blinkTime < 0)
		{
			GetStage()->RemoveGameObject<Blinking>(blinking);
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}


		Col4 color = blinking->GetAdjustedColor();
		drawComp->SetDiffuse(color);


	}
}
