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
		auto scale = Vec3(2.0f,2.0f,1.0f);
		auto fream = AddGameObject<FreamSprite>(L"Fream", pos, scale);
		auto freamTrans = fream->GetComponent<Transform>();
		m_freamPos[gamePadID] = freamTrans->GetPosition();

		fream->SetDrawLayer(0);

		// ステータス項目の生成
		auto stutase = 3;
		Vec3 stutasePos = pos;
		if (gamePadID % 2 == 0) // 左か右か
			 stutasePos.x = pos.x + 62.0f;
		else stutasePos.x = pos.x - 220.0f;

		if (gamePadID < 2) // 上か下
			 stutasePos.y = pos.y - 40;
		else stutasePos.y = pos.y + 110.0f;

		// ゲージ配置
		auto gaugePos = stutasePos;
		for (int i = 0; i < stutase; i++) {
			// ステータスUI
			auto statusUI = AddGameObject<StatusSpriteUI>(gaugePos, i);
			auto stsUIPos = statusUI->GetComponent<Transform>()->GetPosition();
			statusUI->SetDrawLayer(1);

			stsUIPos.x += 150.0f;
			stsUIPos.y -= 27.0f;

			// ゲージ
			auto GaugeBack = AddGameObject<StatusGaugeBack>(stsUIPos);
			GaugeBack->SetDrawLayer(2);
			auto GaugePos = GaugeBack->GetComponent<Transform>()->GetPosition();
			GaugePos += Vec3(3.25f, -2.5f, 0.0f);
			auto gaugeNum = i + (gamePadID * stutase);

			// ゲージ背景
			m_Gauge[gaugeNum] = AddGameObject<StatusGauge>(GaugePos, gamePadID, i);
			m_Gauge[gaugeNum]->SetDrawLayer(3);

			// カラー変更
			auto color = statusUI->StetusColor();
			statusUI->GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
			m_Gauge[gaugeNum]->GetComponent<PCTSpriteDraw>()->SetDiffuse(color);

			gaugePos.y -= 25.0f;
		}
		
		// キャラクターの画像
		auto picturePos = stutasePos;

		picturePos.x = pos.x + 82.0f;
		if (gamePadID < 2)
			 picturePos.y += +140.0f;
		else picturePos.y += - 10.0f;

		// OK!のポジション
		for (int i = 0; i < m_loopForIcon; i++) {
			auto pictureNum = i + (gamePadID * m_loopForIcon);
			m_Picture[pictureNum] = AddGameObject<PlayerCharaPicture>(picturePos,i, gamePadID);
			m_Picture[pictureNum]->SetDrawLayer(1);
			auto OKPos = m_Picture[pictureNum]->GetComponent<Transform>()->GetPosition();
			OKPos += Vec3(-5.0f, +10.0f, 0.0f);
			m_SelectOK[gamePadID] = AddGameObject<OKSpriteUI>(OKPos);
			m_SelectOK[gamePadID]->SetDrawLayer(2);
			m_SelectOK[gamePadID]->SetDrawActive(false);
		}

		PlayerCharacterSelect(gamePadID, stutasePos);

		// プレイヤーのナンバーアイコンの配置
		auto player = AddGameObject<BattlePlayersUIs>(L"BPsUIs", gamePadID + 1, Vec3(0));
		player->GetComponent<PCTSpriteDraw>()->SetDiffuse(playerNum);
		auto playerTrans = player->GetComponent<Transform>();
		
		if (gamePadID % 2 == 0)
			 pos.x += -315;
		else pos.x += 186;

		if (gamePadID < 2)
			pos.y += 175;
		else pos.y += -45;
		playerTrans->SetPosition(pos);
	}
	
	 //アイコン設置
	void CharacterSelectStage::PlayerCharacterSelect(int gamePadID,Vec3 pos) {
		// 三角配置
		auto triPos = pos + Vec3(21, -105, 0);
		auto loopForTri = 2;
		auto tri = gamePadID * loopForTri;

		auto addPosX = 200.f;
		for (int i = 0; i < loopForTri; i++) {
			auto reTri = false;
			if (i == 1) reTri = true;

			m_Triangle[i + tri] = AddGameObject<TriangleSprite>(triPos, reTri);
			auto ptrTrans = m_Triangle[i + tri]->GetComponent<Transform>();
			m_Triangle[i + tri]->SetDrawLayer(1);

			auto setScale = Vec3(0.2f);
			if (reTri) setScale.x *= -1;
			ptrTrans->SetScale(setScale);
			
			triPos.x += addPosX;
		}

		// 左の三角から右の三角までの長さを取る
		auto triPosL = m_Triangle[0 + tri]->GetComponent<Transform>()->GetPosition(); // 左の三角
		auto triPosR = m_Triangle[1 + tri]->GetComponent<Transform>()->GetPosition(); // 右の三角
		auto triPosD = (triPosR - triPosL) / ((float)m_loopForIcon + 1);

		// アイコン設置
		addPosX = addPosX * 0.1f * 1.5f;
		auto iconPos = Vec3(triPosL.x - addPosX, triPosL.y + 7, pos.z + 0);
		auto icons = gamePadID * m_loopForIcon;
		addPosX = triPosD.x;
		for (int i = 0; i < m_loopForIcon; i++) {
			iconPos.x += addPosX;
			m_Icons[i + icons] = AddGameObject<CharaIcon>(iconPos,i);
			auto ptrTrans = m_Icons[i + icons]->GetComponent<Transform>();
			ptrTrans->SetScale(Vec3(0.25f));
			ptrTrans->SetPivot(ptrTrans->GetPosition());
		}

	}

	// UIの設置、OnCreateで使用する関数
	void CharacterSelectStage::UIsSet() {
		AddGameObject<CharacterStringUI>(Vec3(-380, 320, 0))->SetDrawLayer(4);
		AddGameObject<DecisionSpriteUI>(Vec3(260, -320, 0))->SetDrawLayer(4);
		AddGameObject<CancelSpriteUI>(Vec3(-340, -320, 0))->SetDrawLayer(4);
		AddGameObject<AButtonSpriteUI>(Vec3(410, -320, 0))->SetDrawLayer(4);
		AddGameObject<BButtonSpriteUI>(Vec3(-190, -320, 0))->SetDrawLayer(4);
		m_Ready = AddGameObject<ReadyToFightUI>(Vec3(0, 0, 0));

		m_Ready->SetDrawActive(false);
		m_Ready->SetDrawLayer(5);
		m_Ready->SetUpdateActive(false);

		m_GoBackTitleGauge = AddGameObject<GoBackTitleGauge>(Vec3(-426.5f, -285.75f, 0));
		m_GoBackTitleGauge->SetDrawLayer(3);
		AddGameObject<GoBackTitleGaugeBack>(Vec3(-428, -285, 0), m_GoBackTitleGauge)->SetDrawLayer(2);
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

			// フレームのポジション
			auto side = 280.0f;
			auto higth = 150.0f;
			PlayerFreamPosition(Vec3(-side,  higth, 0), 0);
			PlayerFreamPosition(Vec3( side,  higth, 0), 1);
			PlayerFreamPosition(Vec3(-side, -higth, 0), 2);
			PlayerFreamPosition(Vec3( side, -higth, 0), 3);
			UIsSet();

			for (int i = 0; i < m_loopForPlayer; i++) {
				m_charaID[i] = 0;
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

	// キャラクターセレクト
	void CharacterSelectStage::CharacterSelectingPlayers(int gamePadID) {
		auto& app = App::GetApp();
		// コントローラを取得
		const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[gamePadID];

		// 選択中のキャラクターのIDを取得
		SelectCharacter(gamePadID);
		if (ctrlVec.bConnected) {
			// コントローラが接続されていたらtrue
			m_ifEntryPlayer[gamePadID] = true;

			// 決定した場合
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
				m_isDecisionPlayer[gamePadID] = true;
				m_SelectOK[gamePadID]->SetDrawActive(true);

				// 効果音再生
				if (!m_sceneChangeBlock)
					SoundManager::GetInstance()->Play(L"CharacterDecisionSE");
			}
			// キャンセルした場合
			if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
				m_isDecisionPlayer[gamePadID] = false;
				m_SelectOK[gamePadID]->SetDrawActive(false);

				// 効果音再生
				if(!m_sceneChangeBlock)
					SoundManager::GetInstance()->Play(L"CancelSE");
			}
		}
	}

	// キャラクターのIDを取得
	void CharacterSelectStage::GetCharacterID(int gamePadID) {
		// スティック、方向パッド
		const auto& app = App::GetApp();
		const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[gamePadID];

		auto ctrlX = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
		}

		auto moveRight = ctrlX >= 1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		auto moveLeft = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;	
		auto move = 0; // 右なら1、左なら0
		if (!m_isSetStick[gamePadID]) {
			// 右へ
			if (moveRight) {
				m_isSetStick[gamePadID] = true;
				if (m_charaID[gamePadID] < m_iconMaxID) {
					m_charaID[gamePadID]++;
					//m_nowPos = GetComponent<Transform>()->GetPosition();
				}
				else m_charaID[gamePadID] = 0;

				move = 1;
				SoundManager::GetInstance()->Play(L"CharacterSelectingSE");

				// 三角の向き判別番号 + (コントローラID * 三角の個数) 
				auto loopForTri = 2;
				auto tri = move + (gamePadID * loopForTri);
				// 三角形を移動させる
				m_Triangle[tri]->CharacterSelectingAnimation(ctrlVec, m_isSetStick[gamePadID],gamePadID);
			}
			// 左へ
			else if (moveLeft) {
				m_isSetStick[gamePadID] = true;
				if (m_charaID[gamePadID] > 0) {
					m_charaID[gamePadID]--;
					//m_nowPos = GetComponent<Transform>()->GetPosition();
				}
				else m_charaID[gamePadID] = m_iconMaxID;

				move = 0;
				SoundManager::GetInstance()->Play(L"CharacterSelectingSE");

				auto loopForTri = 2;
				auto tri = move + (gamePadID * loopForTri);
				m_Triangle[tri]->CharacterSelectingAnimation(ctrlVec,m_isSetStick[gamePadID], gamePadID);
			}
		}
		else if (!moveLeft && !moveRight) m_isSetStick[gamePadID] = false;

	}

	// キャラクターのIDを元にキャラクターを決める
	void CharacterSelectStage::SelectCharacter(int gamePadID){
		auto setGamePadID = gamePadID + 1; // プレイヤー取得
		switch (m_charaID[gamePadID])
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
	}

	// キャラクターのステータスを表示する
	void CharacterSelectStage::CharacterStetusGauge(int gamePadID) {
		auto stutasNum = 3;
		for (int i = 0; i < stutasNum; i++) {
			auto controlNum = i + gamePadID * stutasNum;
			m_Gauge[controlNum]->GetCharaStutas(m_charaID[gamePadID],i);
		}
	}

	// 表示するキャラクターの画像
	void CharacterSelectStage::DrawCharaPicture(int gamePadID) {
		auto icons = gamePadID * m_loopForIcon;
		for (int i = 0; i < m_loopForIcon; i++) {
			auto pictureNum = i + (gamePadID * m_loopForIcon);
			m_Picture[pictureNum]->SetDrawActive(false);

			// 選んでいるアイコンは明るく表示する
			auto iconComp = m_Icons[i + icons]->GetComponent<PCTSpriteDraw>();
			auto rgba = iconComp->GetDiffuse();
			if (m_charaID[gamePadID] == i) {
				rgba.x = 1;
				rgba.y = 1;
				rgba.z = 1;
			}
			else {
				rgba.x = 0.5f;
				rgba.y = 0.5f;
				rgba.z = 0.5f;
			}
			iconComp->SetDiffuse(rgba);

		}
		// 全体の写真を表示する
		auto pictureNum = m_charaID[gamePadID] + (gamePadID * m_loopForIcon);
		m_Picture[pictureNum]->SetDrawActive(true);
	}

	//// キャラクターの選択が完了
	//void CharacterSelectStage::CharacterSelectedPlayers(int gamePadID) {
	//	if (m_isDecisionPlayer[gamePadID]) {

	//	}
	//	else {

	//	}
	//}

	// 全員がキャラクターの選択を完了しているか
	void CharacterSelectStage::CheckSelectedPlayers() {
		auto color = m_BackGround->GetComponent<PCTSpriteDraw>();
		auto rgba = color->GetDiffuse();
		if (m_isDecisionPlayer[0] && m_isDecisionPlayer[1] &&
			m_isDecisionPlayer[2] && m_isDecisionPlayer[3])
		{
			m_Ready->SetDrawActive(true);
			m_Ready->SetUpdateActive(true);
			rgba.x = 0.5f;
			rgba.y = 0.5f;
			rgba.z = 0.5f;
		}
		else if (m_isDecisionPlayer[0] || m_isDecisionPlayer[1] ||
				 m_isDecisionPlayer[2] || m_isDecisionPlayer[3])
		{
			m_Ready->SetDrawActive(false);
			m_Ready->SetUpdateActive(false);
			rgba.x = 1;
			rgba.y = 1;
			rgba.z = 1;
		}
		color->SetDiffuse(rgba);
	}

	// ゲームステージへ移動
	void  CharacterSelectStage::GoToGameStage() {
		auto& app = App::GetApp();
		for (int i = 0; i < m_loopForPlayer; i++) {
			const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[i];

			if (ctrlVec.bConnected) {
				// ゲーム開始
				if ( ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A &&	// Aボタンを押す
					!m_sceneChangeBlock &&							// まだシーン変異イベントを起こしていない
					 m_Ready->GetUpdateActive()) {					// Ready to Fight!! のスプライトが表示されている

					PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
					m_sceneChangeBlock = true;
				}
			}
		}

	}

	// タイトルへ戻る
	void  CharacterSelectStage::GoBackTitle() {
		auto goBackTitle = m_GoBackTitleGauge->GetGoBackTitle();

		if (goBackTitle) {
			auto& app = App::GetApp();
			PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
			m_sceneChangeBlock = true;
		}
	}

	void CharacterSelectStage::OnUpdate() {
		auto& app = App::GetApp();
		for (int i = 0; i < m_loopForPlayer; i++) {
			CharacterSelectingPlayers(i);
			CharacterStetusGauge(i);
			DrawCharaPicture(i);
			if(!m_isDecisionPlayer[i]) GetCharacterID(i);

			const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[i];
			if (!ctrlVec.bConnected) {
				m_ifEntryPlayer[i] = false;
				m_isDecisionPlayer[i] = true;
				m_SelectOK[i]->SetDrawActive(true);
			}
		}

		// 順番が違うと正常に機能しなくなる
		GoToGameStage();		// ゲームを開始する
		GoBackTitle();			// タイトルへ戻る
		CheckSelectedPlayers(); // 全員がキャラクターを選択したか
	}

	void CharacterSelectStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}