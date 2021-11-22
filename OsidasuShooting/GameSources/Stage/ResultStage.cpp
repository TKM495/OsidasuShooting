/*!
@file   ResultStage.cpp
@brief  リザルトステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
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

	void ResultStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : ResultStage");

			auto allPlayer = PlayerManager::GetInstance()->GetSortedAllPlayer();
			for (auto player : allPlayer) {
				wstring str = L"";
				switch (player->GetPlayerNumber())
				{
				case PlayerNumber::P1:
					str = L"P1";
					break;
				case PlayerNumber::P2:
					str = L"P2";
					break;
				case PlayerNumber::P3:
					str = L"P3";
					break;
				case PlayerNumber::P4:
					str = L"P4";
					break;
				default:
					break;
				}
				Debug::GetInstance()->Log(str);
				Debug::GetInstance()->Log(player->GetCountKilledPlayer());
			}
			PlayerManager::DeleteInstance();

			Debug::GetInstance()->Log(L"Button A → Game");
			Debug::GetInstance()->Log(L"Button B → Title");
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto& app = App::GetApp();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_B)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
	}
}