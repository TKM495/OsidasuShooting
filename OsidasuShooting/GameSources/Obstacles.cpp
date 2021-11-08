#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Obstacles::OnCreate()
	{
		auto drawComp = AddComponent <BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrColl = AddComponent <CollisionSphere>();

		auto transComp = GetComponent<Transform>();
		auto transPos = transComp->GetPosition(); //(x,y,z)


		transPos.x += 2;
		transComp->SetPosition(transPos);
	}

}
//end basecross