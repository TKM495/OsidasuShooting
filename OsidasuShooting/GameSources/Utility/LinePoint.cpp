#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LinePoint::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(1.0, 0.0f, 0.0f, 1.0f));
	}
}