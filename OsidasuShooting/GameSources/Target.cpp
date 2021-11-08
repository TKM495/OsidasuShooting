#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Target::OnCreate()
	{
		auto stage = GetStage();

		auto drawComp = AddComponent <BcPNTStaticDraw>();
		auto PtrColl = AddComponent<CollisionObb>();

		drawComp->SetMeshResource(L"DEFAULT_CUBE");


		executeTime = stage->GetSharedGameObject<ListsOfVariable>(L"ListsOfVariable")->executeTime;


	}


	void Target::OnUpdate()
	{

		auto& app = App::GetApp();


		auto stage = GetStage();
		auto getVariable = stage->GetSharedGameObject<ListsOfVariable>(L"ListsOfVariable");

		auto transComp = GetComponent<Transform>();
		auto transPos = transComp->GetPosition(); //(x,y,z)


		float deltaTime = app->GetElapsedTime();
		float speed = getVariable->speed;


		//実際に以下を実行されます
		/*
		Vec3 direction = getVariable->direction;


		if (direction.x != 0) {
			transPos.x += speed * deltaTime;
		}
		if (direction.y != 0) {
			transPos.y += speed * deltaTime;
		}
		if (direction.z != 0) {
			transPos.z += speed * deltaTime;
		}
		*/
		//実際に上記を実行されます


		//一時的に書きました。。。。あとで消します
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['A'])
		{
			transPos.x += -speed * deltaTime;
		}if (KeyState.m_bPushKeyTbl['D'])
		{
			transPos.x += speed * deltaTime;
		}if (KeyState.m_bPushKeyTbl['W'])
		{
			transPos.z += speed * deltaTime;
		}if (KeyState.m_bPushKeyTbl['S'])
		{
			transPos.z += -speed * deltaTime;
		}
		//一時的に書きました。。。。あとで消します...end


		if (executeTime> 0)
		{
			executeTime-= deltaTime;
			transComp->SetPosition(transPos);

			//Debug::GetInstance()->Log(Util::FloatToWStr(executeTime));

			int seconds = (int)executeTime;
			auto m_ssComp = AddComponent<StringSprite>();
			m_ssComp->SetText(L"Time: " + Util::IntToWStr(seconds) + L" Seconds ......  キーボードを使用する（A、D、S、W）");


		}else{
			GetStage()->RemoveGameObject<Target>(GetThis<Target>());
		}
		
	}

	void Target::OnCollisionEnter(shared_ptr<GameObject>& other)
	{

		auto stage = GetStage();
		bool doDestroy = false;//消えるの許可

		if (other->FindTag(L"Destroied By Target"))
		{
			doDestroy = true;
		}

		if (doDestroy)
		{
			GetStage()->RemoveGameObject<Target>(GetThis<Target>());
		}
	}
}
//end basecross