/*!
@file   TitleStage.cpp
@brief  タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
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
	
	void TitleStage::AddTitleSprite()
	{
		AddGameObject<TitleSprite>(L"Title", false,
			Vec2(256.0f, 50.0f), Vec2(0.0f, 50.0f));
	}


	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : TitleStage");
			Debug::GetInstance()->Log(L"A : GameStart");
			Debug::GetInstance()->Log(L"B : Exit");

			AddTitleSprite();
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_B)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToExit");
	}
}