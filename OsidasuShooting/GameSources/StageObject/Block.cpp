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

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		ObjectSetUp();
	}

	void Block::OnUpdate() {
	}
}