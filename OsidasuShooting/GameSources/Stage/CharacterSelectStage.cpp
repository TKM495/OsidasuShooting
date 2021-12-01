#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CharacterSelectStage::CreateViewLight() {
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
	

	void CharacterSelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : CharacterSelectStage");
			Debug::GetInstance()->Log(L"A : GameStart");
			Debug::GetInstance()->Log(L"B : ToTitle");

			float posOffsetX = 128.0f;
			float posOffsetY = 100.0f;
			
			auto icons = AddGameObject<CharacterIcon>(L"LaserIcon");
			auto iconTrans = icons->GetComponent<Transform>();

			auto posSet = -posOffsetX + m_shiftMovePos;

			iconTrans->SetPosition(Vec3(posSet, posOffsetY, 0));

			//auto addIcons = AddGameObject<CharacterIcon>(L"MissileIcon");
			//auto addIconTrans = addIcons->GetComponent<Transform>();
			//addIconTrans->SetPosition(Vec3(-posOffsetX + m_shiftMovePos, posOffsetY, 0));

			Debug::GetInstance()->Log(iconTrans->GetPosition());
			//Debug::GetInstance()->Log(addIconTrans->GetPosition());
			Debug::GetInstance()->Log(m_shiftMovePos);
		}
		catch (...) {
			throw;
		}
	}

	void CharacterSelectStage::SetCharaName() {
	}

	void CharacterSelectStage::OnUpdate() {
		auto& app = App::GetApp();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_B)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
	}
}
