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
	void CharacterSelectStage::PlayerFreamPosition(Vec3 pos, int gamePadID) {
		m_gamePadIDs[gamePadID] = gamePadID;	// ゲームパッドの番号を登録
		m_isDecisionPlayer[gamePadID] = false;

		auto scale = 2.0f;
		auto fream = AddGameObject<FreamSprite>(L"Fream", pos, scale);
		auto freamTrans = fream->GetComponent<Transform>();
		m_freamPos[gamePadID] = freamTrans->GetPosition();
		fream->SetDrawLayer(0);

		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[gamePadID];
		PlayerCharacterSelect(m_freamPos[gamePadID], gamePadID);
		PlayerSelectTriangle(m_freamPos[gamePadID], Vec3(0.5f), gamePadID);
	}

	// アイコン設置
	void CharacterSelectStage::PlayerCharacterSelect(Vec3 pos, int gamePadID) {
		for (int i = 0; i < 3; i++) {
			auto gamePadLinkIcons = i + 3 * gamePadID;
			m_Icons[gamePadLinkIcons] = AddGameObject<CharacterIcon>(m_charaName[i], gamePadID, m_shiftMovePos, pos);
			auto iconTrans = m_Icons[gamePadLinkIcons]->GetComponent<Transform>();

			auto posSet = m_posOffsetX + m_shiftMovePos * (i + 1);

			iconTrans->SetPosition(pos + Vec3(posSet, m_posOffsetY, 0));
			m_Icons[gamePadLinkIcons]->SetDrawLayer(1);
			// Debug::GetInstance()->Log(iconTrans->GetPosition().x);
		}

		auto player = AddGameObject<BattlePlayersUIs>(L"BPsUIs", gamePadID + 1, Vec3(0));
		auto playerTrans = player->GetComponent<Transform>();
		pos.y += 10;
		playerTrans->SetPosition(pos);
	}

	// 三角設置
	void CharacterSelectStage::PlayerSelectTriangle(Vec3 pos, Vec3 scl, int gamePadID) {
		// 正位置

		m_Triangle[gamePadID] = AddGameObject<SelectTriangle>(L"Triangle", gamePadID, 0, pos, scl, false);
		auto triTrans = m_Triangle[gamePadID]->GetComponent<Transform>();

		auto posX = pos.x + 190;
		auto posY = pos.y - 60.0f;

		triTrans->SetPosition(Vec3(-m_shiftMovePos + posX, posY, 0));
		triTrans->SetScale(scl);
		m_Triangle[gamePadID]->SetDrawLayer(1);

		m_Triangle[gamePadID + 4] = AddGameObject<SelectTriangle>(L"ReTriangle", gamePadID, 0, pos, scl, true);
		triTrans = m_Triangle[gamePadID + 4]->GetComponent<Transform>();
		triTrans->SetPosition(Vec3(m_shiftMovePos + posX, posY, 0));
		triTrans->SetScale(scl);
		m_Triangle[gamePadID + 4]->SetDrawLayer(1);
	}
	 // UIの設置、OnCreateで使用する関数
	void CharacterSelectStage::UIsSet() {
		AddGameObject<CharacterStringUI>(Vec3(0, 320, 0));
		AddGameObject<DecisionSpriteUI>(Vec3(260, -320, 0));
		AddGameObject<CancelSpriteUI>(Vec3(-340,-320 , 0));
		AddGameObject<AButtonSpriteUI>(Vec3(410, -320, 0));
		AddGameObject<BButtonSpriteUI>(Vec3(-190, -320, 0));
		m_Ready = AddGameObject<ReadyToFightUI>(Vec3(0, 0, 0));

		m_Ready->SetDrawActive(false);
		m_Ready->SetUpdateActive(false);
	}

	void CharacterSelectStage::SetCharaName() {
		//m_charaName[i] = cvs;

		m_charaName[0] = (L"LaserIcon");
		m_charaName[1] = (L"MissileIcon");
		m_charaName[2] = (L"3WayIcon");
		//m_charaName[3] = (L"MissileIcon");
	}

	void CharacterSelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : CharacterSelectStage");
			Debug::GetInstance()->Log(L"A : GameStart");
			Debug::GetInstance()->Log(L"B : ToTitle");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			SetCharaName();
			auto side = 300.0f;
			auto higth = 150.0f;
			PlayerFreamPosition(Vec3(-side, higth, 0), 0);
			PlayerFreamPosition(Vec3(side, higth, 0), 1);
			PlayerFreamPosition(Vec3(-side, -higth, 0), 2);
			PlayerFreamPosition(Vec3(side, -higth, 0), 3);

			UIsSet();

			for (int i = 0; i < m_loopForPlayer; i++) {
				CharacterSelectingPlayers(m_gamePadIDs[i]);
				Debug::GetInstance()->Log(m_isDecisionPlayer[i]);
			}
			//auto addIcons = AddGameObject<CharacterIcon>(L"MissileIcon");
			//Debug::GetInstance()->Log(m_shiftMovePos);
			//Debug::GetInstance()->Log(m_shiftMovePos);
			AddGameObject<TransitionSprite>()->FadeOut();

			SoundManager::GetInstance()->PlayLoop(L"SelectBGM");
		}
		catch (...) {
			throw;
		}
	}

	void CharacterSelectStage::CharacterSelectingPlayers(int gamePadID) {
		auto& app = App::GetApp();
		const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[gamePadID];
		if (ctrlVec.bConnected) {
			m_ifEntryPlayer[gamePadID] = true;
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
				m_isDecisionPlayer[gamePadID] = true;
				SoundManager::GetInstance()->Play(L"CharacterDecisionSE");
			}
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
				m_isDecisionPlayer[gamePadID] = false;
				SoundManager::GetInstance()->Play(L"CancelSE");
			}
		}
		else {
			m_ifEntryPlayer[gamePadID] = false;
			m_isDecisionPlayer[gamePadID] = true;
		}
	}

	void CharacterSelectStage::CharacterSelectedPlayers(int gamePadID) {
		if (m_isDecisionPlayer[gamePadID]) {
			m_Triangle[gamePadID]->SetDrawActive(false);
			m_Triangle[gamePadID]->SetUpdateActive(false);

			m_Triangle[gamePadID + 4]->SetDrawActive(false);
			m_Triangle[gamePadID + 4]->SetUpdateActive(false);

			for (int i = 0; i < 3; i++) {
				auto gamePadLinkIcons = i + 3 * gamePadID;
				m_Icons[gamePadLinkIcons]->SetUpdateActive(false);
			}
		}
		else {
			m_Triangle[gamePadID]->SetDrawActive(true);
			m_Triangle[gamePadID]->SetUpdateActive(true);

			m_Triangle[gamePadID + 4]->SetDrawActive(true);
			m_Triangle[gamePadID + 4]->SetUpdateActive(true);

			for (int i = 0; i < 3; i++) {
				auto gamePadLinkIcons = i + 3 * gamePadID;
				m_Icons[gamePadLinkIcons]->SetUpdateActive(true);
			}
		}
	}

	void CharacterSelectStage::CheckSelectedPlayers() {
		if (m_isDecisionPlayer[0] && m_isDecisionPlayer[1] &&
			m_isDecisionPlayer[2] && m_isDecisionPlayer[3])
		{
			m_Ready->SetDrawActive(true);
			m_Ready->SetUpdateActive(true);
		}
		else if (m_isDecisionPlayer[0] || m_isDecisionPlayer[1] ||
			m_isDecisionPlayer[2] || m_isDecisionPlayer[3])
		{
			m_Ready->SetDrawActive(false);
			m_Ready->SetUpdateActive(false);

			auto& app = App::GetApp();
			for (int i = 0; i < m_loopForPlayer; i++) {
				const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[i];
				if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
					if (m_isBPushPlayer[i]) {
						PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
					}
					else m_isBPushPlayer[i] = true;
				}
			}
		}
	}

	void CharacterSelectStage::OnUpdate() {
		auto& app = App::GetApp();
		for (int i = 0; i < m_loopForPlayer; i++) {
			CharacterSelectingPlayers(i);
			CharacterSelectedPlayers(i);

			const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[i];
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
				m_isBPushPlayer[i] = false;
			}
		}
		CheckSelectedPlayers();
	}

	void CharacterSelectStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}