/*!
@file   DebugStage.cpp
@brief  各種ステージに遷移できるデバッグ用のステージの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void DebugStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void DebugStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
		}
		catch (...) {
			throw;
		}
	}

	void DebugStage::OnUpdate() {
	}
}