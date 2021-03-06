/*!
@file   WatanabeStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	void WatanabeStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<GameCamera>();
		PtrView->SetCamera(PtrCamera);
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
			EfkEffectResource::RegisterEffectResource(L"Hit", TestEffectStr + L"Hit.efk");
			EfkEffectResource::RegisterEffectResource(L"Jump", TestEffectStr + L"Jump.efk");
			EfkEffectResource::RegisterEffectResource(L"Hover", TestEffectStr + L"Hover.efk");
			EfkEffectResource::RegisterEffectResource(L"Bomb", TestEffectStr + L"Bomb.efk");
			EfkEffectResource::RegisterEffectResource(L"Smoke", TestEffectStr + L"Smoke.efk");
			EfkEffectResource::RegisterEffectResource(L"Laser", TestEffectStr + L"Laser.efk");
			EfkEffectResource::RegisterEffectResource(L"Respawn", TestEffectStr + L"Respawn.efk");
			EfkEffectResource::RegisterEffectResource(L"BreakBlock", TestEffectStr + L"BreakBlock.efk");			//ビューとライトの作成
			EfkEffectResource::RegisterEffectResource(L"Shield", TestEffectStr + L"Shield.efk");
			EfkEffectResource::RegisterEffectResource(L"Buff", TestEffectStr + L"Buff.efk");

			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage");

			//XMLファイル
			XMLLoad::GetInstance()->RegisterFile(L"PlayerStatus", DataDir + L"XML/" + L"PlayerStatus.xml");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", DataDir + L"CSV/" + L"PlayerInfo.csv");

			PlayerStatus::GetInstance()->DataExtraction();
			auto dir_ = App::GetApp()->GetDataDirWString();
			auto path_ = dir_ + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path_ + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path_ + L"PlayerFollowUI.csv");

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<Bumper>(L"Bumper");
			builder.Register<ReflectorBlock>(L"Reflector");
			builder.Register<BreakBlock>(L"BreakableBlock");
			builder.Register<PlayerBuilder>(L"Player");
			builder.Register<FallDecision>(L"FallDecision");
			builder.Register<MoveBlock>(L"MovingBlock");
			builder.Register<CameraArea>(L"CameraArea");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/";
			builder.Build(GetThis<Stage>(), path + L"Stage1.csv");
			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			m_itemCreation = AddGameObject<modifiedClass::ItemCreation>();
			auto out = AddGameObject<ColorOut>();
			//out->SetActive(true);
			out->SetColor(Col4(1, 0, 0, 0.5f));
			out->SetRange(1.0f, 0.95f);
			out->SetRate(4.0f);
		}
		catch (...) {
			throw;
		}
	}

	void WatanabeStage::OnUpdate() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		const auto& con = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (keyState.m_bPressedKeyTbl['R'] || con.wPressedButtons & XINPUT_GAMEPAD_Y)
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage");
		if (con.wPressedButtons & XINPUT_GAMEPAD_X) {
			auto item = AddGameObject<modifiedClass::Item>(modifiedClass::ItemType::Bomb);
			item->GetComponent<Transform>()->SetPosition(Vec3(0, 5, 0));
		}
		if (keyState.m_bPressedKeyTbl['W']) {
			m_itemCreation->SpawnInRandPosition();
		}
		if (keyState.m_bPressedKeyTbl['D']) {
			StageManager::GetInstance()->SetPlayerType(1, PlayerType::Missile);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage");
		}
		if (keyState.m_bPressedKeyTbl['A']) {
			StageManager::GetInstance()->SetPlayerType(1, PlayerType::Laser);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage");
		}
		if (keyState.m_bPressedKeyTbl['P']) {
			SoundManager::GetInstance()->Play(L"FinishSE", 0, 1);
			Debug::GetInstance()->Log(L"PlaySE");
		}
	}

	void WatanabeStage::OnDestroy() {
		m_controller.ResetVibration();
		PlayerManager::GetInstance()->DeleteInstance();
	}
}