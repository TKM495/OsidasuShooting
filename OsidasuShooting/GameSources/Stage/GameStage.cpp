/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "TestObject.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<DebugCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//ObjectFactory::Create<EfkInterface>(GetThis<GameStage>());
			AddGameObject<EfkInterface>();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring TestEffectStr = DataDir + L"Effects\\test.efk";

			EfkEffectResource::RegisterEffectResource(L"Test", TestEffectStr);

			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Debug>();

			AddGameObject<TestObject>();

			AddGameObject<Block>(Vec3(0.0f, -1.5f, 0.0f), Vec3(10.0f, 1.0f, 10.0f));
		}
		catch (...) {
			throw;
		}
	}
}
//end basecross