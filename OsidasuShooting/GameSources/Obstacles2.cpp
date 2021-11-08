#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Obstacles2::OnCreate()
	{
		auto drawComp = AddComponent <BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		Col4 color(1.0f, 1.0f, 0.5f, 1.0f);
		drawComp->SetColorAndAlpha(color);

		auto PtrColl = AddComponent <CollisionSphere>();

		auto transComp = GetComponent<Transform>();
		auto transPos = transComp->GetPosition(); //(x,y,z)


		transPos.x += 3;
		transComp->SetPosition(transPos);
	}

}
//end basecross