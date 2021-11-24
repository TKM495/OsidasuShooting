#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Items::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.0f));

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(0.5f,0.5f,0.5f));
	}
}
