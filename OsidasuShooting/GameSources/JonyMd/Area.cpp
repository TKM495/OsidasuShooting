#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Area::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.0f,1.0f,0.0f,0.0f));

		auto transCom = GetComponent<Transform>();
		auto transScale = transCom->GetScale();
		auto transPos = transCom->GetPosition();

		transScale.x = 6;
		transScale.y = 0.2;
		transScale.z = 3;
		transCom->SetScale(transScale);
	}

}
