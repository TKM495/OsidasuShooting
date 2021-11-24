/*!
@file   WatanabeStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	void WatanabeStage2::CreateViewLight() {
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

	void WatanabeStage2::OnCreate() {
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
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage2");

			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			AddGameObject<Block>(TransformData(Vec3(0.0f, -1.0f, 0.0f)));

			auto player = AddGameObject<ManualPlayer>(TransformData(Vec3(0.0f, 1.0f, 0.0f)), PlayerNumber::P1);
			//AddGameObject<PlayerInfo>(player, TransformData());
			//AddGameObject<PlayerFollowUI>(player, TransformData());
			AddGameObject<BattlePlayersUIs>(L"BPsUIs", 6, Vec3(0));
			PlayerManager::GetInstance()->AddPlayer(player);

			AddGameObject<SimpleSprite>(L"Test", TransformData(Vec3(0.0f), Vec3(0.4f)))->SetDrawLayer(-2);
		}
		catch (...) {
			throw;
		}
	}

	void WatanabeStage2::OnUpdate() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (keyState.m_bPressedKeyTbl['R'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage");
	}
}