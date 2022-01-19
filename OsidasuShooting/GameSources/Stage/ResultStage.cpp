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

	void ResultStage::AddWinnerSprite(int player)
	{
		if (m_isTopOnly) {
			auto winnerUIs = AddGameObject<ResultWinOrDrowSprite>(Vec3(-280, -220, 0), m_isTopOnly);
			auto winnerUIsTrans = winnerUIs->GetComponent<Transform>();
			auto winnerUIsPos = winnerUIsTrans->GetPosition();

			auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player, Vec3(0));
			playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerTopColor);
			auto playUIsTrans = playerNumber->GetComponent<Transform>();
			playUIsTrans->SetPosition(winnerUIsPos - Vec3(-412.0f, -27.0f, 0));
			playUIsTrans->SetScale(Vec3(1.1f));
		}
		else AddGameObject<ResultWinOrDrowSprite>(Vec3(-190, -220, 0), m_isTopOnly);
	}

	void ResultStage::AddResultSprites(Vec3 pos, int playerNum, int score, int dead)
	{
		auto fream = AddGameObject<FreamSprite>(L"Fream", pos, Vec3(1.2f));
		auto freamTrans = fream->GetComponent<Transform>();
		auto freamPos = freamTrans->GetPosition();
		fream->SetDrawLayer(1);
		//freamTrans->SetPosition(resultPos);

		auto playerColor = PlayerStatus::GetInstance()->GetPlayerColor(playerNum);
		auto playerNumPos = pos;
		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", playerNum, Vec3(0));
		playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(playerColor);
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		playerNumPos.x -= 160.0f;
		playerNumPos.y += 90.0f;
		playUIsTrans->SetPosition(playerNumPos);
		playUIsTrans->SetScale(Vec3(0.4f));
		playerNumber->SetDrawLayer(2);

		auto scorePos = pos;
		scorePos.x += 50.0f;
		scorePos.y += 65.0f;	
		m_score = AddGameObject<ResultScore>(score, scorePos);
		m_score->SetDrawLayer(2);
		scorePos.y -= 60.0f;
		auto deadPos = scorePos;

		scorePos.x -= 50;
		scorePos.y += 24;
		AddGameObject<KillIcon>(scorePos)->SetDrawLayer(2);

		m_dead = AddGameObject<ResultScore>(dead, deadPos);
		m_dead->SetDrawLayer(2);
		deadPos.x -= 50;
		deadPos.y -= 36;
		AddGameObject<DeadIcon>(deadPos)->SetDrawLayer(2);
		
	}


	void ResultStage::PlayersResult() {
		float addVec = 0;
		float setPosY = 0;

		auto allPlayer = PlayerManager::GetInstance()->GetSortedAllPlayer();
		int loopCount = 0; // for
		int drawPlayer = 0;
		for (auto player : allPlayer) {
			str = L"";
			switch (player->GetPlayerNumber())
			{
			case PlayerNumber::P1:
				str = L"P1";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor = PlayerStatus::GetInstance()->GetPlayerColor(loopCount + 1);
				break;
			case PlayerNumber::P2:
				str = L"P2";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor = PlayerStatus::GetInstance()->GetPlayerColor(loopCount + 1);
				break;
			case PlayerNumber::P3:
				str = L"P3";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor = PlayerStatus::GetInstance()->GetPlayerColor(loopCount + 1);
				break;
			case PlayerNumber::P4:
				str = L"P4";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor = PlayerStatus::GetInstance()->GetPlayerColor(loopCount + 1);
				break;
			default:
				break;
			}

			//Debug::GetInstance()->Log(str);
			//Debug::GetInstance()->Log(player->GetCountKilledPlayer());

			AddResultSprites(Vec3(400 + addVec, 250 + setPosY, 0), 
				(UINT)m_playersNumber + 1, m_playersScore, m_playersDead);
			addVec += 12.5f;
			setPosY -= 170;

			auto winer	  = player->GetCountKilledPlayer() > m_playerTopScore;
			auto deadWin  = player->GetCountKilledPlayer() == m_playerTopScore && player->GetDeadCount() < m_playerTopDead;
			auto drawDead = player->GetCountKilledPlayer() == m_playerTopScore && player->GetDeadCount() == m_playerTopDead;

			if (loopCount == 0 || winer || deadWin) {
				m_playerTop = m_playersNumber;
				m_playerTopScore = m_playersScore;
				m_playerTopDead = m_playersDead;
				m_playerTopColor = m_playerColor;
				m_isTopOnly = true;
			}
			else if (drawDead) {
				m_playerDraw[drawPlayer] = m_playersNumber;
				m_isTopOnly = false;
				drawPlayer++;
			}
			loopCount++;
		}
		// トップのプレイヤー
		m_playerTop = allPlayer[0]->GetPlayerNumber();
	}

	void ResultStage::WinnerPlayer() {
		PlayersResult();
		auto player = PlayerNumber::P1;
		if ((int)m_playerTop == 2) {
			player = PlayerNumber::P2;
		}
		else if ((int)m_playerTop == 3) {
			player = PlayerNumber::P3;
		}
		else if ((int)m_playerTop == 4) {
			player = PlayerNumber::P4;
		}
		auto topPlayer = AddGameObject<ResultPlayer>(
			TransformData(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.75f), Vec3(0, XMConvertToRadians(180.0f), 0)),
			m_playerTop, StageManager::GetInstance()->GetPlayerType(m_playerTop));
		//topPlayer->GetComponent<Gravity>()->SetGravityZero();
		auto PlayerPos = topPlayer->GetComponent<Transform>()->GetPosition();

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

			//ビューとライトの作成
			CreateViewLight();
			//AddGameObject<Debug>();
			//Debug::GetInstance()->Log(L"CurrentStage : ResultStage");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			PlayersResult();
			WinnerPlayer();

			PlayerManager::DeleteInstance();

			AddWinnerSprite((UINT)m_playerTop + 1);

			Debug::GetInstance()->Log(L"Button A : CharacterSelect");
			Debug::GetInstance()->Log(L"Button B : Title");

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
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];
		if (!m_sceneChangeBlock) {
			if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A) {
				SoundManager::GetInstance()->Play(L"DecisionSE");
				PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToCharacterSelectStage");
				m_sceneChangeBlock = true;
			}
			if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_B) {
				SoundManager::GetInstance()->Play(L"DecisionSE");
				PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
				m_sceneChangeBlock = true;
			}
		}
	}

	void ResultStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}