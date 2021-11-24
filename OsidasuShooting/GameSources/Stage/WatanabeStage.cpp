/*!
@file   WatanabeStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	void WatanabeStage::CreateViewLight() {
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

	void WatanabeStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring TestEffectStr = DataDir + L"Effects\\";
			EfkEffectResource::RegisterEffectResource(L"Bullet", TestEffectStr + L"Bullet.efk");
			EfkEffectResource::RegisterEffectResource(L"Explosion", TestEffectStr + L"fire.efk");

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage");

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage";
			path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			auto player = AddGameObject<ManualPlayer>(TransformData(Vec3(10.0f, 1.0f, -15.0f)), PlayerNumber::P1);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(-500.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			player = AddGameObject<ManualPlayer>(TransformData(Vec3(-10.0f, 1.0f, 15.0f)), PlayerNumber::P2);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(-200.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			player = AddGameObject<ManualPlayer>(TransformData(Vec3(-10.0f, 1.0f, 0.0f)), PlayerNumber::P3);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(200.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			player = AddGameObject<ManualPlayer>(TransformData(Vec3(10.0f, 1.0f, 0.0f)), PlayerNumber::P4);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(500.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			AddGameObject<FallDecision>();
		}
		catch (...) {
			throw;
		}
	}

	void WatanabeStage::OnUpdate() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (keyState.m_bPressedKeyTbl['R'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage");
	}
}