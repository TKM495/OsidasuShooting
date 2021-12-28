/*!
@file   WatanabeStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	void WatanabeStage::CreateViewLight() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CSVLoad::GetInstance()->RegisterFile(L"Camera", DataDir + L"CSV/" + L"Camera.csv");
		auto line = CSVLoad::GetInstance()->GetData(L"Camera");
		auto data = DataExtracter::DelimitData(line[1]);
		const Vec3 eye = Vec3(
			(float)_wtof(data[1].c_str()),
			(float)_wtof(data[2].c_str()),
			(float)_wtof(data[3].c_str())
		);
		const Vec3 at = Vec3(
			(float)_wtof(data[4].c_str()),
			(float)_wtof(data[5].c_str()),
			(float)_wtof(data[6].c_str())
		);
		//const Vec3 eye(0.0f, 25.0f, -30.0f);
		//const Vec3 at(0.0f, 0.0f, -7.0f);
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
			EfkEffectResource::RegisterEffectResource(L"BombPlus", TestEffectStr + L"BombPlus.efk");
			EfkEffectResource::RegisterEffectResource(L"Respawn", TestEffectStr + L"Respawn.efk");
			EfkEffectResource::RegisterEffectResource(L"BreakBlock", TestEffectStr + L"BreakBlock.efk");			//ビューとライトの作成

			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage");

			//XMLファイル
			XMLLoad::GetInstance()->RegisterFile(L"PlayerStatus", DataDir + L"XML/" + L"PlayerStatus.xml");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", DataDir + L"CSV/" + L"PlayerInfo.csv");

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<Bumper>(L"Bumper");
			builder.Register<ReflectorBlock>(L"Reflecter");
			builder.Register<BreakBlock>(L"BreakableBlock");
			builder.Register<PlayerBuilder>(L"Player");
			builder.Register<FallDecision>(L"FallDecision");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/";
			builder.Build(GetThis<Stage>(), path + L"StageBase.csv");
			builder.Build(GetThis<Stage>(), path + L"Stage1.csv");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);
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
	}

	void WatanabeStage::OnDestroy() {
		m_controller.ResetVibration();
	}
}