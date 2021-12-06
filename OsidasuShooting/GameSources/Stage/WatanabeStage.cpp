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
		auto PtrCamera = ObjectFactory::Create<DebugCamera>(20.0f, 5.0f);
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

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage");

			//XMLファイル
			XMLLoad::GetInstance()->RegisterFile(L"PlayerStatus", DataDir + L"XML/" + L"PlayerStatus.xml");

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<PlayerBuilder>(L"Player");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/Stage1";
			path += L".csv";

			builder.Build(GetThis<Stage>(), path);

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