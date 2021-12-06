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
	
	// フレーム設置
	void CharacterSelectStage::PlayerFreamPosition(Vec3 pos,int gamePadID) {
		auto scale = 2.0f;
		auto fream = AddGameObject<FreamSprite>(L"Fream",pos,scale);
		auto freamTrans = fream->GetComponent<Transform>();
		fream->SetDrawLayer(0);

		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[gamePadID];
		//if (ctrlVec.bConnected) {
			PlayerCharacterSelect(freamTrans->GetPosition(), gamePadID);
			PlayerSelectTriangle(freamTrans->GetPosition(), Vec3(0.5f), gamePadID);
		//}


	}

	// アイコン設置
	void CharacterSelectStage::PlayerCharacterSelect(Vec3 pos, int gamePadID) {

		for (int i = 0; i < 4; i++) {
			auto icons = AddGameObject<CharacterIcon>(m_charaName[i], gamePadID, m_shiftMovePos, pos);
			auto iconTrans = icons->GetComponent<Transform>();

			auto posSet = m_posOffsetX + m_shiftMovePos * (i + 1);

			iconTrans->SetPosition(pos + Vec3(posSet, m_posOffsetY, 0));
			icons->SetDrawLayer(1);
		}
	}

	// 三角設置
	void CharacterSelectStage::PlayerSelectTriangle(Vec3 pos, Vec3 scl, int gamePadID) {
		// 正位置

		auto triangle = AddGameObject<SelectTriangle>(L"Triangle", gamePadID, 0, pos, scl,false);
		auto triTrans = triangle->GetComponent<Transform>();

		auto posX = pos.x + 190;
		auto posY = pos.y - 60.0f;

		triTrans->SetPosition(Vec3(-m_shiftMovePos + posX, posY, 0));
		triTrans->SetScale(scl);
		triangle->SetDrawLayer(1);

		triangle = AddGameObject<SelectTriangle>(L"ReTriangle", gamePadID, 0, pos, scl, true);
		triTrans = triangle->GetComponent<Transform>();
		triTrans->SetPosition(Vec3(m_shiftMovePos + posX, posY, 0));
		triTrans->SetScale(scl);
		triangle->SetDrawLayer(1);

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
			auto side = 300.0f;
			auto higth = 150.0f;
			PlayerFreamPosition(Vec3(-side,  higth, 0), 0);
			PlayerFreamPosition(Vec3( side,  higth, 0), 1);
			PlayerFreamPosition(Vec3(-side, -higth, 0), 2);
			PlayerFreamPosition(Vec3( side, -higth, 0), 3);


			//auto addIcons = AddGameObject<CharacterIcon>(L"MissileIcon");
			//Debug::GetInstance()->Log(m_shiftMovePos);
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
