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
		// カラーの取得
		auto playerNum = PlayerStatus::GetInstance()->GetPlayerColor(gamePadID + 1);

		// ゲームパッドの番号を登録
		m_gamePadIDs[gamePadID] = gamePadID;	
		m_isDecisionPlayer[gamePadID] = false;

		// フレームの生成
		auto scale = Vec3(2.0f,1.5f,1.0f);
		auto fream = AddGameObject<FreamSprite>(L"Fream", pos, scale);
		auto freamTrans = fream->GetComponent<Transform>();
		m_freamPos[gamePadID] = freamTrans->GetPosition();

		fream->SetDrawLayer(0);

		// ステータス項目の生成
		auto stutase = 3;
		Vec3 stutasePos = pos;
		if (gamePadID % 2 == 0)
			 stutasePos.x = pos.x + 62.0f;
		else stutasePos.x = pos.x - 220.0f;

		if (gamePadID > 1)
			 stutasePos.y = pos.y + 110.0f;
		else stutasePos.y = pos.y - 60.0f;

		// ゲージ配置
		auto gaugePos = stutasePos;
		for (int i = 0; i < stutase; i++) {
			auto statusUI = AddGameObject<StatusSpriteUI>(gaugePos, i);
			auto stsUIPos = statusUI->GetComponent<Transform>()->GetPosition();
			statusUI->SetDrawLayer(1);

			stsUIPos.x += 150.0f;
			stsUIPos.y -= 27.0f;
			auto GaugeBack = AddGameObject<StatusGaugeBack>(stsUIPos);
			auto GaugePos = GaugeBack->GetComponent<Transform>()->GetPosition();
			GaugePos += Vec3(3.25f, -2.5f, 0.0f);
			auto gaugeNum = i + (gamePadID * stutase);
			m_Gauge[gaugeNum] = AddGameObject<StatusGauge>(GaugePos, gamePadID, i);

			// カラー変更
			auto color = statusUI->StetusColor();
			statusUI->GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
			m_Gauge[gaugeNum]->GetComponent<PCTSpriteDraw>()->SetDiffuse(color);

			gaugePos.y -= 25.0f;
		}
		
		// キャラクターの画像
		auto pictchar = m_loopForIcon; // キャラ数 = キャラアイコン数
		auto picturePos = stutasePos;

		picturePos.x = pos.x + 82.0f;
		if (gamePadID > 1)
			 picturePos.y += -40.0f;
		else picturePos.y += +140.0f;
		for (int i = 0; i < pictchar; i++) {
			auto pictureNum = i + (gamePadID * m_loopForIcon);
			m_Picture[pictureNum] = AddGameObject<PlayerCharaPicture>(picturePos,i, gamePadID);
			m_Picture[pictureNum]->SetDrawLayer(1);
		}

		auto player = AddGameObject<BattlePlayersUIs>(L"BPsUIs", gamePadID + 1, Vec3(0));
		player->GetComponent<PCTSpriteDraw>()->SetDiffuse(playerNum);
		auto playerTrans = player->GetComponent<Transform>();
		
		if (gamePadID % 2 == 0)
			 pos.x += -315;
		else pos.x += 186;
		if(gamePadID < 2)
			 pos.y += 157;
		else pos.y += -28;
		playerTrans->SetPosition(pos);
	}
	
	// アイコン設置
	void CharacterSelectStage::PlayerCharacterSelect(Vec3 pos) {
		auto addPosX = 100;
		for (int i = 0; i < m_loopForIcon; i++) {
			m_Icons[i] = AddGameObject<CharaIcon>(pos,i);
			pos.x += addPosX;
		}
	}

	// UIの設置、OnCreateで使用する関数
	void CharacterSelectStage::UIsSet() {
		AddGameObject<CharacterStringUI>(Vec3(-380, 320, 0));
		AddGameObject<DecisionSpriteUI>(Vec3(260, -320, 0));
		AddGameObject<CancelSpriteUI>(Vec3(-340, -320, 0));
		AddGameObject<AButtonSpriteUI>(Vec3(410, -320, 0));
		AddGameObject<BButtonSpriteUI>(Vec3(-190, -320, 0));
		m_Ready = AddGameObject<ReadyToFightUI>(Vec3(0, 0, 0));

		m_Ready->SetDrawActive(false);
		m_Ready->SetUpdateActive(false);
	}

	void CharacterSelectStage::PlayerCursorCreate(int gamePadID){
		// カラーの取得
		auto playerNum = PlayerStatus::GetInstance()->GetPlayerColor(gamePadID + 1);
		// 初期位置
		auto defaultPos = m_Icons[0]->GetComponent<Transform>()->GetPosition();
		// カーソル生成
		m_SelectCursor[gamePadID] = AddGameObject<SelectCursor>(defaultPos, gamePadID);
		// カラー変更
		m_SelectCursor[gamePadID]->GetComponent<PCTSpriteDraw>()->SetDiffuse(playerNum);
		// アイコンの数だけループ
		for (int i = 0; i < m_loopForIcon; i++) {
			// 各アイコンのポジションを取得
			auto iconPos = m_Icons[i]->GetComponent<Transform>()->GetPosition();
			m_SelectCursor[gamePadID]->GetIconDatas(i,iconPos);
		}
	}

	void CharacterSelectStage::SetCharaName() {
		//m_charaName[i] = cvs;

		m_charaName[0] = (L"LaserIcon");
		m_charaName[1] = (L"TankIcon");
		//m_charaName[2] = (L"3WayIcon");
		//m_charaName[3] = (L"MissileIcon");
	}

	void CharacterSelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//AddGameObject<Debug>();
			//Debug::GetInstance()->Log(L"CurrentStage : CharacterSelectStage");
			//Debug::GetInstance()->Log(L"A : GameStart");
			//Debug::GetInstance()->Log(L"B : ToTitle");

			m_BackGround = AddGameObject<SimpleSprite>(L"BackGround00");
			m_BackGround->SetDrawLayer(-1);

			auto scale = Vec3(10.0f, 1.5f, 1.0f);
			auto fream = AddGameObject<FreamSprite>(L"GaugeBackGround", Vec3(0), scale);
			auto ptrDraw = fream->GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f,1.0f,1.0f,0.5f));

			SetCharaName();
			auto side = 280.0f;
			auto higth = 170.0f;
			PlayerFreamPosition(Vec3(-side,  higth, 0), 0);
			PlayerFreamPosition(Vec3( side,  higth, 0), 1);
			PlayerFreamPosition(Vec3(-side, -higth, 0), 2);
			PlayerFreamPosition(Vec3( side, -higth, 0), 3);
			PlayerCharacterSelect(Vec3(-50.0f, 0.0f, 0.0f));
			UIsSet();

			for (int i = 0; i < m_loopForPlayer; i++) {

				PlayerCursorCreate(i);
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
		SelectCharacter(gamePadID);
		if (ctrlVec.bConnected) {
			m_ifEntryPlayer[gamePadID] = true;

			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
				m_isDecisionPlayer[gamePadID] = true;

				m_SelectCursor[gamePadID]->SetDrawActive(false);
				m_SelectCursor[gamePadID]->SetUpdateActive(false);

				if (!m_sceneChangeBlock)
					SoundManager::GetInstance()->Play(L"CharacterDecisionSE");
			}
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
				m_isDecisionPlayer[gamePadID] = false;
				
				m_SelectCursor[gamePadID]->SetDrawActive(true);
				m_SelectCursor[gamePadID]->SetUpdateActive(true);

				if(!m_sceneChangeBlock)
					SoundManager::GetInstance()->Play(L"CancelSE");
			}
		}
	}

	void CharacterSelectStage::SelectCharacter(int gamePadID){
		int charaID = m_SelectCursor[gamePadID]->SetCharacterID();
		auto setGamePadID = gamePadID + 1;
		switch (charaID)
		{
		case 0:
			StageManager::GetInstance()->SetPlayerType(setGamePadID, PlayerType::Laser);
			break;

		case 1:
			StageManager::GetInstance()->SetPlayerType(setGamePadID, PlayerType::Missile);
			break;

		default:
			break;
		}
		CharacterStetusGauge(gamePadID);
		DrawCharaPicture(gamePadID);
	}

	// キャラクターのステータスを表示する
	void CharacterSelectStage::CharacterStetusGauge(int gamePadID) {
		int charaID = m_SelectCursor[gamePadID]->SetCharacterID();
		auto stutasNum = 3;
		for (int i = 0; i < stutasNum; i++) {
			auto controlNum = i + gamePadID * stutasNum;
			m_Gauge[controlNum]->GetCharaStutas(charaID,i);
		}
	}

	// 表示するキャラクターの画像
	void CharacterSelectStage::DrawCharaPicture(int gamePadID) {
		for (int i = 0; i < m_loopForIcon; i++) {
			auto pictureNum = i + (gamePadID * m_loopForIcon);
			m_Picture[pictureNum]->SetDrawActive(false);
		}

		int charaID = m_SelectCursor[gamePadID]->SetCharacterID();
		auto pictureNum = charaID + (gamePadID * m_loopForIcon);
		m_Picture[pictureNum]->SetDrawActive(true);
	}

	// キャラクターの選択が完了、コントローラが繋がれていない場合はカーソルを非表示
	void CharacterSelectStage::CharacterSelectedPlayers(int gamePadID) {
		if (m_isDecisionPlayer[gamePadID]) {
			m_SelectCursor[gamePadID]->SetDrawActive(false);
			m_SelectCursor[gamePadID]->SetUpdateActive(false);

		}
		else {
			m_SelectCursor[gamePadID]->SetDrawActive(true);
			m_SelectCursor[gamePadID]->SetUpdateActive(true);

		}
	}

	// キャラクターの選択を完了しているか
	void CharacterSelectStage::CheckSelectedPlayers() {
		auto& app = App::GetApp();
		for (int i = 0; i < m_loopForPlayer; i++) {
			const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[i];
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A 
				&& !m_sceneChangeBlock && m_Ready->GetUpdateActive()) {
				PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
				m_sceneChangeBlock = true;
			}
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_B
				&& !m_sceneChangeBlock && !m_Ready->GetUpdateActive()) {
				if (m_isBPushPlayer[i]) {
					PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
					m_sceneChangeBlock = true;
				}
				else m_isBPushPlayer[i] = true;
			}
		}

		auto color = m_BackGround->GetComponent<PCTSpriteDraw>();
		auto rgba = color->GetDiffuse();
		if (m_isDecisionPlayer[0] && m_isDecisionPlayer[1] &&
			m_isDecisionPlayer[2] && m_isDecisionPlayer[3])
		{
			//m_CharaSelectFream->SetDrawActive(false);
			m_Ready->SetDrawActive(true);
			m_Ready->SetUpdateActive(true);
			rgba.x = 0.5f;
			rgba.y = 0.5f;
			rgba.z = 0.5f;
		}
		else if (m_isDecisionPlayer[0] || m_isDecisionPlayer[1] ||
			m_isDecisionPlayer[2] || m_isDecisionPlayer[3])
		{
			//m_CharaSelectFream->SetDrawActive(true);
			m_Ready->SetDrawActive(false);
			m_Ready->SetUpdateActive(false);
			rgba.x = 1;
			rgba.y = 1;
			rgba.z = 1;
		}
		color->SetDiffuse(rgba);
		for (int i = 0; i < m_loopForIcon; i++) {
			auto ptrDraw = m_Icons[i]->GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(rgba);
		}
	}

	void CharacterSelectStage::OnUpdate() {
		auto& app = App::GetApp();
		for (int i = 0; i < m_loopForPlayer; i++) {
			CharacterSelectingPlayers(i);

			const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[i];
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
				m_isBPushPlayer[i] = false;
			}

			if (!ctrlVec.bConnected) {
				m_ifEntryPlayer[i] = false;
				m_isDecisionPlayer[i] = true;
				m_SelectCursor[i]->SetDrawActive(false);
				m_SelectCursor[i]->SetUpdateActive(false);
			}
		}
		CheckSelectedPlayers();
	}

	void CharacterSelectStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}