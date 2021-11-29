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
		const Vec3 at(0.5f, 0.0f, -2.0f);
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
		auto winnerUIs = AddGameObject<ResultWinnerSprite>(L"Winner");
		auto winnerUIsTrans = winnerUIs->GetComponent<Transform>();
		auto winnerUIsPos = winnerUIsTrans->GetPosition();

		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", 1, Vec3(0));
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		playUIsTrans->SetPosition(winnerUIsPos - Vec3(-412.0f, -27.0f, 0));
		playUIsTrans->SetScale(Vec3(1.1f));

	}

	void ResultStage::AddResultDataSprite(Vec3 pos, int playerNum, int score)
	{
		auto fream = AddGameObject<ResultFreamSprite>(L"ResultFream");
		auto freamTrans = fream->GetComponent<Transform>();
		auto freamPos = freamTrans->GetPosition();
		auto resultPos = freamPos + pos;
		freamTrans->SetPosition(resultPos);

		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", playerNum, Vec3(0));
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		resultPos.y -= 50.0f;
		playUIsTrans->SetPosition(resultPos);
		playUIsTrans->SetScale(Vec3(0.4f));

		resultPos.x += 120.0f;
		resultPos.y += 25.0f;
		m_score = AddGameObject<ResultScore>(score, resultPos);
		m_score->SetDrawLayer(1);
	}

	void ResultStage::PlayersResult() {

		float addVec = 0;
		float setPosY = 0;

		auto allPlayer = PlayerManager::GetInstance()->GetSortedAllPlayer();
		int i = 0; // for
		for (auto player : allPlayer) {
			str = L"";
			switch (player->GetPlayerNumber())
			{
			case PlayerNumber::P1:
				str = L"P1";
				m_playersNumber = 1;
				m_playersScore = player->GetCountKilledPlayer();
				break;
			case PlayerNumber::P2:
				str = L"P2";
				m_playersNumber = 2;
				m_playersScore = player->GetCountKilledPlayer();
				break;
			case PlayerNumber::P3:
				str = L"P3";
				m_playersNumber = 3;
				m_playersScore = player->GetCountKilledPlayer();
				break;
			case PlayerNumber::P4:
				str = L"P4";
				m_playersNumber = 4;
				m_playersScore = player->GetCountKilledPlayer();
				break;
			default:
				break;
			}
			Debug::GetInstance()->Log(str);
			Debug::GetInstance()->Log(player->GetCountKilledPlayer());
			AddResultDataSprite(Vec3(390 + addVec, 260 + setPosY, 0), m_playersNumber, m_playersScore);
			setPosY -= 160;
			if (i > 0) {
				m_playerTop = m_playersNumber;
				m_playerTopScore = m_playersScore;
			}
			else {
				if (player->GetCountKilledPlayer() > m_playerTopScore) {
					m_playerTop = m_playersNumber;
					m_playerTopScore = m_playersScore;
				}
			}
		}
	}

	void ResultStage::WinnerPlayer() {
		PlayersResult();
		auto Player1 = AddGameObject<ManualPlayer>(TransformData(Vec3(0), Vec3(1), Vec3(0, 0, 1)), PlayerNumber::P1);
		Player1->GetComponent<Gravity>()->SetGravityZero();
		auto PlayerPos = Player1->GetComponent<Transform>()->GetPosition();

		auto Laser = AddGameObject<SpecialLaser>(Player1, Vec3(0, 0, 0), Vec3(0, 0, 0));

		AddGameObject<Block>(TransformData(Vec3(0, -1, 0), Vec3(100, 1, 100)));
	}

	void ResultStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : ResultStage");

			WinnerPlayer();

			PlayerManager::DeleteInstance();

			AddWinnerSprite(m_playersNumber);

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