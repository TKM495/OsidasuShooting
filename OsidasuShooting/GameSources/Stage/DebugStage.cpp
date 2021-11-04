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
			Debug::GetInstance()->Log(L"CurrentStage : DebugStage");
			Debug::GetInstance()->Log(L"W → WatanabeStage");
			Debug::GetInstance()->Log(L"S → SatoStage");
			Debug::GetInstance()->Log(L"J → JONYMDStage");
			Debug::GetInstance()->Log(L"M → GameStage");
		}
		catch (...) {
			throw;
		}
	}

	void DebugStage::OnUpdate() {
		const auto& app = App::GetApp();
		const auto& keyState = app->GetInputDevice().GetKeyState();
		if (keyState.m_bPressedKeyTbl['W'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToWatanabeStage");
		else if (keyState.m_bPressedKeyTbl['S'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToSatoStage");
		else if (keyState.m_bPressedKeyTbl['J'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToJONYMDStage");
		else if (keyState.m_bPressedKeyTbl['M'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
	}
}