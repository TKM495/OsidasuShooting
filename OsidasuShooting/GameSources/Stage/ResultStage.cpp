/*!
@file   ResultStage.cpp
@brief  リザルトステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
		//const Vec3 eye(0.0f, 5.0f, -5.0f);
		//const Vec3 at(0.0f);
		const Vec3 eye(0.0f, 0.0f, -4.0f);
		const Vec3 at(0.4f, 0.0f, -2.0f);
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

	// WinnerあるいはDrawを表示する
	void ResultStage::AddWinnerSprite(int player)
	{
		// トップが一人の場合
		if (m_isTopOnly) {
			// Winnerの位置を設定する
			Vec3 winnerUIsPos = Vec3(-280, -220, 0); // 位置を設定する
			auto winnerUIs = AddGameObject<ResultWinOrDrowSprite>(winnerUIsPos, m_isTopOnly);
			auto winnerUIsTrans = winnerUIs->GetComponent<Transform>();
			winnerUIsPos = winnerUIsTrans->GetPosition(); // 正確な設置場所に更新

			// プレイヤーナンバーの位置を決定する
			auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player, Vec3(0));
			playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerTopColor);	// プレイヤーのカラー
			auto playUIsTrans = playerNumber->GetComponent<Transform>();
			// プレイヤーのナンバーの場所
			Vec3 playerNumberPos = winnerUIsPos - Vec3(-412.0f, -27.0f, 0);				// ナンバーの設置場所を設定
			playUIsTrans->SetPosition(playerNumberPos);
			Vec3 scale = Vec3(1.1f);
			playUIsTrans->SetScale(scale);
		}
		// トップが二人以上の場合
		else {
			// Drawの文字の表示位置
			Vec3 drawUIsPos = Vec3(-160, -120, 0);
			float posX = drawUIsPos.x; // ほかの場所でも使用するので変数にする
			auto drawUIs = AddGameObject<ResultWinOrDrowSprite>(drawUIsPos, m_isTopOnly);
			auto drawUIsTrans = drawUIs->GetComponent<Transform>();
			drawUIsPos = drawUIsTrans->GetPosition();

			auto resultDrawPlayer = 1;	// 1人以上は確実に表示するため、あらかじめ1を代入
			auto maxDrawPlayer = 3;		// for文ループ回数、追加で更に最大3人表示するので3を代入
			for (int i = 0; i < maxDrawPlayer; i++) {
				if (m_isPlayerDraw[i] == true) {
					resultDrawPlayer++;
				}
			}

			// 順番が早いプレイヤーの表示
			auto playerNum = 0;
			auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player, Vec3(0));	// 配置
			playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerColor[playerNum]);	// カラーをセット
			auto playUIsTrans = playerNumber->GetComponent<Transform>();

			// ポジション
			auto setPosition = Vec3(posX * 2.175f, -170.0f, 1.0f);
			// スケール
			Vec3 v3Scale = Vec3(0.75f);
			float fScale = 1.1f;
			auto setScale = v3Scale * (1 - 0.1f * (resultDrawPlayer * fScale));

			playUIsTrans->SetPosition(setPosition);
			playUIsTrans->SetScale(Vec3(setScale));

			// それ以降のプレイヤー
			auto setPosX = posX * 2.25f / resultDrawPlayer;
			for (int i = 0; i < maxDrawPlayer; i++) {
				playerNum++;
				if (m_isPlayerDraw[i] == true) {
					setPosition.x -= setPosX;
					auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player + playerNum, Vec3(0));
					playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerColor[playerNum]);
					auto playUIsTrans = playerNumber->GetComponent<Transform>();
					playUIsTrans->SetPosition(setPosition);
					playUIsTrans->SetScale(Vec3(setScale));
				}
			}
		}
	}

	// 各プレイヤーの情報を表示
	void ResultStage::AddResultSprites(Vec3 pos, int playerNum, int score, int dead, int rank)
	{
		// フレームを配置
		Vec3 scale = Vec3(1.2f);
		auto fream = AddGameObject<FreamSprite>(L"Fream", pos, scale);
		auto freamTrans = fream->GetComponent<Transform>();
		auto freamPos = freamTrans->GetPosition();
		fream->SetDrawLayer(1);

		// カラー取得
		auto playerColor = PlayerStatus::GetInstance()->GetPlayerColor(playerNum);
		// 設置するポジション
		auto playerNumPos = pos + Vec3(-200.0f, 115.0f, 0.0f);
		// プレイヤーのナンバーを表示する
		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", playerNum, Vec3(0));
		// ナンバーに色を付ける
		playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(playerColor);

		// プレイヤーナンバーの設置
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		playUIsTrans->SetPosition(playerNumPos);

		scale = Vec3(0.4f);
		playUIsTrans->SetScale(scale);
		playerNumber->SetDrawLayer(2);

		// プレイヤーの順位を表示
		RankingPlayerSet(pos, rank);

		// プレイヤーのキルスコア
		auto scorePos = pos + Vec3(50.0f, 65.0f, 1.0f);			// キルスコアのポジション設定
		m_score = AddGameObject<ResultScore>(score, scorePos);	// 配置
		m_score->SetDrawLayer(2);
		
		auto addIconPos = Vec3(-50.0f, -36.0f, 0.0f);

		auto killIconPos = scorePos + addIconPos;				// アイコンのポジション
		AddGameObject<KillIcon>(killIconPos)->SetDrawLayer(2);	// 配置

		// プレイヤーのデススコア
		auto deadPos = Vec3(scorePos.x, scorePos.y - 60.0f, scorePos.z);	// キルスコアのポジション設定
		m_dead = AddGameObject<ResultScore>(dead, deadPos);					// 配置
		m_dead->SetDrawLayer(2);
		auto deadIconPos = deadPos + addIconPos;							// アイコンのポジション
		AddGameObject<DeadIcon>(deadIconPos)->SetDrawLayer(2);				// 配置
	}

	// プレイヤーの順位表示
	void ResultStage::RankingPlayerSet(Vec3 pos, int value) {
		auto playerRank = AddGameObject<BattlePlayersUIs>(L"RRUIs", value, Vec3(0));
		Vec3 addPos = Vec3(-165.0f, 75.0f, 0.0f);
		auto rankIconPos = pos + addPos;
		auto rankIconTrans = playerRank->GetComponent<Transform>();
		rankIconTrans->SetPosition(rankIconPos);
	}

	// プレイヤーの順位
	void ResultStage::PlayersResult() {
		float addVec = 0;
		float setPosY = 0;

		auto allPlayer = PlayerManager::GetInstance()->GetSortedAllPlayer();
		int  loopCount = 0;	// for文
		int  drawPlayer = 0;// 表示するプレイヤーの数
		int  draw = 0;		// 引き分け
		bool isDraw = false;

		// 順位が高い順に処理される
		for (auto player : allPlayer) {
			str = L"";
			switch (player->GetPlayerNumber())
			{
			case PlayerNumber::P1:
				str = L"P1";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P1);
				break;
			case PlayerNumber::P2:
				str = L"P2";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P2);
				break;
			case PlayerNumber::P3:
				str = L"P3";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P3);
				break;
			case PlayerNumber::P4:
				str = L"P4";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P4);
				break;
			default:
				break;
			}

			// プレイヤーの順位の処理
			auto top = m_playersScore > m_playerTopScore;		// 参照されたプレイヤーのキルスコアが暫定トップより高い場合
			auto killeDraw = m_playersScore == m_playerTopScore;// 参照されたプレイヤーのキルスコアが暫定トップと同じな場合
			
			// トップのデススコア比較
			auto topDeadWin  = killeDraw && m_playersDead  < m_playerTopDead; // デススコアが暫定トップより少ないとき
			auto topDrawDead = killeDraw && m_playersDead == m_playerTopDead; // デススコアが暫定トップと同じとき
			auto drawDead = 
				 m_previousScore == m_playersScore && m_previousDead == m_playersDead; // デススコアが前の順位のプレイヤーと同じとき

			// 比較
			// トップになった場合
			if (loopCount == 0 || top || topDeadWin) {
				m_playerTop = m_playersNumber;
				m_playerTopScore = m_playersScore;
				m_playerTopDead = m_playersDead;
				m_playerTopColor = m_playerColor[loopCount];
				m_isTopOnly = true;
			}
			else if (topDrawDead || drawDead) {
				m_playerDraw[drawPlayer] = m_playersNumber;
				if (topDrawDead) {
					m_isTopOnly = false;
					m_isPlayerDraw[drawPlayer] = true;
				}
				drawPlayer++;
				draw++;
				isDraw = true;
			}
			else {
				draw = 0;
			}
			auto rankingNum = loopCount - draw;

			// プレイヤーの結果を表示する
			AddResultSprites(Vec3(400 + addVec, 250 + setPosY, 0),
				(UINT)m_playersNumber + 1, m_playersScore, m_playersDead, rankingNum);

			//Debug::GetInstance()->Log(draw);
			addVec += 12.5f;
			setPosY -= 170;

			loopCount++;

			// 比較用に別の関数に代入
			m_previousScore = m_playersScore;
			m_previousDead = m_playersDead;
		}

		// トップのプレイヤー
		//m_playerTop = allPlayer[0]->GetPlayerNumber();
	}

	// 行事するプレイヤー
	void ResultStage::WinnerPlayer() {
		PlayersResult();

		// トップが一人のとき
		if (m_isTopOnly) {
			auto scale = Vec3(0.75f);
			auto topPlayer = AddGameObject<ResultPlayer>(
				TransformData(Vec3(0.0f, 1.0f, 0.0f), scale, Vec3(0, XMConvertToRadians(180.0f), 0)),
				m_playerTop, StageManager::GetInstance()->GetPlayerType(m_playerTop));

			auto playerPos = topPlayer->GetComponent<Transform>()->GetPosition();
			playerPos += Vec3(-1.0f, 2.0f,0);
			auto confetti = AddGameObject<Confetti>(playerPos);
			topPlayer->PlayWin();
		}
		// トップが二人以上のとき
		else {
			auto maxDrawPlayer = 3;
			auto resultDrawPlayer = 0;
			auto posX = 0.5f;
			for (int i = 0; i < maxDrawPlayer; i++) {
				if (m_isPlayerDraw[i] == true) {
					resultDrawPlayer++;
				}
			}

			auto resultPosX = -resultDrawPlayer;
			auto setPosX = 0.75f;
			auto setPosZ = (float)resultDrawPlayer;
			auto setScale = Vec3(0.65f) * (1 - 0.1f * (resultDrawPlayer * 1.25f));

			auto topPlayer = AddGameObject<ResultPlayer>(
				TransformData(Vec3(resultPosX * setPosX, 1.0f, setPosZ), setScale, Vec3(0, XMConvertToRadians(180.0f), 0)),
				m_playerTop, StageManager::GetInstance()->GetPlayerType(m_playerTop));

			for (int i = 0; i < maxDrawPlayer; i++) {
				if (m_isPlayerDraw[i] == true) {
					resultPosX += 2;
					auto drawPlayer = AddGameObject<ResultPlayer>(
						TransformData(Vec3(resultPosX * setPosX, 1.0f, setPosZ), setScale, Vec3(0, XMConvertToRadians(180.0f), 0)),
						m_playerDraw[i], StageManager::GetInstance()->GetPlayerType(m_playerDraw[i]));
					posX += 1.0f;
					resultDrawPlayer++;
				}
			}
		}
		AddGameObject<Block>(TransformData(Vec3(0, -1, 0), Vec3(100, 1, 100)));
	}

	void ResultStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();
			auto efkpath = App::GetApp()->GetDataDirWString() + L"Effects/";
			EfkEffectResource::RegisterEffectResource(L"Bullet", efkpath + L"Bullet.efk");
			EfkEffectResource::RegisterEffectResource(L"Explosion", efkpath + L"fire.efk");
			EfkEffectResource::RegisterEffectResource(L"Hit", efkpath + L"Hit.efk");
			EfkEffectResource::RegisterEffectResource(L"Jump", efkpath + L"Jump.efk");
			EfkEffectResource::RegisterEffectResource(L"Hover", efkpath + L"Hover.efk");
			EfkEffectResource::RegisterEffectResource(L"Bomb", efkpath + L"Bomb.efk");
			EfkEffectResource::RegisterEffectResource(L"Smoke", efkpath + L"Smoke.efk");
			EfkEffectResource::RegisterEffectResource(L"Smoke", efkpath + L"Smoke.efk");

			//ビューとライトの作成
			CreateViewLight();
			//AddGameObject<Debug>();
			//Debug::GetInstance()->Log(L"CurrentStage : ResultStage");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			//PlayersResult();
			WinnerPlayer();

			PlayerManager::DeleteInstance();

			AddWinnerSprite((UINT)m_playerTop + 1);

			//Debug::GetInstance()->Log(L"Button A : CharacterSelect");
			//Debug::GetInstance()->Log(L"Button B : Title");

			SoundManager::GetInstance()->PlayLoop(L"ResultBGM");

			AddGameObject<GoToSelectSpriteUI>(Vec3(-0, -320, 0));
			AddGameObject<GoToTitleSpriteUI>(Vec3(-430, -320, 0));
			AddGameObject<AButtonSpriteUI>(Vec3(120, -320, 0));
			AddGameObject<BButtonSpriteUI>(Vec3(-310, -320, 0));
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto& app = App::GetApp();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec();

		auto cntl = 4 - 1; // 最大コントローラ数 - 1
		for (int i = 0; i <= cntl; i++) {
			if (!m_sceneChangeBlock) {
				// キャラクターセレクトに戻る
				if (cntlPad[i].wPressedButtons & XINPUT_GAMEPAD_A) {
					SoundManager::GetInstance()->Play(L"DecisionSE");
					PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToCharacterSelectStage");
					m_sceneChangeBlock = true;
				}
				// タイトル画面に戻る
				if (cntlPad[i].wPressedButtons & XINPUT_GAMEPAD_B) {
					SoundManager::GetInstance()->Play(L"DecisionSE");
					PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
					m_sceneChangeBlock = true;
				}
			}
		}
	}

	void ResultStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}