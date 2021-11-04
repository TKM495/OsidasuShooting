/*!
@file CameraTester.cpp
@brief カメラのテストのターゲット実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	TargetObj::TargetObj(const shared_ptr<Stage>& stage)
		: GameObject(stage)
	{}

	void TargetObj::OnCreate()
	{
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1,1,1);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(0,0,0);
	}

	void TargetObj::OnUpdate()
	{
	}

}
//end basecross