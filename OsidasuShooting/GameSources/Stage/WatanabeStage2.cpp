/*!
@file   WatanabeStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	void WatanabeStage2::CreateViewLight() {
		const Vec3 eye(0.0f, 20.0f, -20.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetFovY(XMConvertToRadians(90));
		//PtrCamera->set
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void WatanabeStage2::OnCreate() {
		try {
			AddGameObject<EfkInterface>();

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage2");

			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			PlayerStatus::GetInstance()->DataExtraction();

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<Bumper>(L"Bumper");
			builder.Register<ReflectorBlock>(L"Reflector");
			builder.Register<BreakBlock>(L"BreakableBlock");
			builder.Register<PlayerBuilder>(L"Player");
			builder.Register<FallDecision>(L"FallDecision");
			builder.Register<MoveBlock>(L"MovingBlock");
			dir = App::GetApp()->GetDataDirWString();
			path = dir + L"Csv/Stage/";
			builder.Build(GetThis<Stage>(), path + L"TitleStage.csv");
			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			GetView()->GetTargetCamera()->SetCameraObject(AddGameObject<TitleCamera>());
			GetView()->GetTargetCamera()->SetUp(Vec3(0.2f, 0.9f, 0).normalize());
			m_confetti = AddGameObject<Confetti>(TransformData(Vec3(0, 5, 0)));
		}
		catch (...) {
			throw;
		}
	}

	void WatanabeStage2::OnUpdate() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		const auto& cont = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cont.wPressedButtons & XINPUT_GAMEPAD_Y || keyState.m_bPressedKeyTbl['R'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage2");
		if (keyState.m_bPressedKeyTbl['W']) {
			m_confetti->GetComponent<EfkComponent>()->Play(L"Hit");
		}
	}
}