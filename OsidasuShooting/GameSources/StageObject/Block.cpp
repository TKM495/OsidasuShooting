/*!
@file   Block.cpp
@brief  ブロッククラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Block::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.0f));
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		ObjectSetUp();
	}

	void Block::OnUpdate() {
	}
}