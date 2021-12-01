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

			SetCharaName();

			for (int i = 0; i < 4; i++) {
				auto icons = AddGameObject<CharacterIcon>(m_charaName[i]);
				auto iconTrans = icons->GetComponent<Transform>();

				auto posSet = m_posOffsetX + m_shiftMovePos * i;

				iconTrans->SetPosition(Vec3(posSet, m_posOffsetY, 0));
			}
			//auto addIcons = AddGameObject<CharacterIcon>(L"MissileIcon");
			Debug::GetInstance()->Log(m_shiftMovePos);
		}
		catch (...) {
			throw;
		}
	}

	void CharacterSelectStage::SetCharaName() {	

		//m_charaName[i] = cvs;

		m_charaName[0] = (L"LaserIcon");
		m_charaName[1] = (L"MissileIcon");
		m_charaName[2] = (L"3WayIcon");
		m_charaName[3] = (L"MissileIcon");

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
