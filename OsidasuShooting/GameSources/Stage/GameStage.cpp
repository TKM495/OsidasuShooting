/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<GameCamera>();
		PtrView->SetCamera(PtrCamera);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : GameStage");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-2);
			AddGameObject<BackPlanet>(L"Planet")->SetDrawLayer(-1);

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<Bumper>(L"Bumper");
			builder.Register<ReflectorBlock>(L"Reflector");
			builder.Register<BreakBlock>(L"BreakableBlock");
			builder.Register<PlayerBuilder>(L"Player");
			builder.Register<FallDecision>(L"FallDecision");
			builder.Register<CameraArea>(L"CameraArea");
			builder.Register<MoveBlock>(L"MovingBlock");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/";
			builder.Build(GetThis<Stage>(), path + L"Stage1.csv");

			auto countDown = AddGameObject<CountDown>(34.0f);
			SetSharedGameObject(L"ForCountDown", countDown);
			countDown->SetDrawLayer(1);
			m_startCountDown = AddGameObject<StartCountDown>(TransformData());
			m_itemCreation = AddGameObject<modifiedClass::ItemCreation>();

			AddGameObject<TransitionSprite>()->FadeOut();
			SoundManager::GetInstance()->PlayLoop(L"Game1BGM");

			auto out = AddGameObject<ColorOut>();
			out->SetColor(Col4(1, 0.5f, 0, 0));
			out->SetRange(0.3f, 0.1f);
			out->SetRate(4.0f);
			auto trigger = AddGameObject<OnceTriggerObject>();
			trigger->SetFunction(
				L"Remaining30Sec",
				[=]() {
					out->SetActive(true);
					Remaining30Sec();
				}
			);
			trigger->SetFunction(
				L"Remaining10Sec",
				[this] {
					SoundManager::GetInstance()->Play(L"WarningSE");
					AddGameObject<CountDown10Sec>(TransformData());
				}
			);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto m_countDown = GetSharedGameObject<CountDown>(L"ForCountDown");
		switch (m_gameState)
		{
		case GameState::FADEOUT:
			// フェードが終了したら
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
				m_startCountDown->IsStart(true);
				auto allPlayer = PlayerManager::GetInstance()->GetAllPlayer();
				for (auto player : allPlayer) {
					player->SetActive(true);
					player->GetComponent<EfkComponent>()->Play(L"Respawn");
				}
				ChangeGameState(GameState::STAY);
			}
			break;
		case GameState::STAY:
			if (m_startCountDown->GetTimer().IsTimeUp()) {
				m_countDown->Start();
				Debug::GetInstance()->Log(L"GameStart！！！！！");
				ChangeGameState(GameState::PLAYING);
			}
			break;
		case GameState::PLAYING:
			// アイテムの生成
			ItemGeneration();

			if (m_countDown->GetTime() < 31.0f) {
				m_isTurnOff30Sec = true;
				auto trigger = GetSharedGameObject<OnceTriggerObject>(L"OnceTriggerObject");
				trigger->LaunchFunction(L"Remaining30Sec");
			}
			if (m_countDown->GetTime() < 11.0f) {
				auto trigger = GetSharedGameObject<OnceTriggerObject>(L"OnceTriggerObject");
				trigger->LaunchFunction(L"Remaining10Sec");
			}

			if (m_countDown->GetTime() <= 1.0f) {
				m_countDown->Stop();
				m_utilTimer.Reset(3.0f);
				AddGameObject<FinishSprite>(TransformData());
				Debug::GetInstance()->Log(L"Finish!!!!!!");
				ChangeGameState(GameState::CLEAR);
			}
			break;
		case GameState::CLEAR:
			//m_timeScale = 0.2f;
			if (m_utilTimer.Count()) {
				TransitionSprite::GetInstance()->FadeIn();
				ChangeGameState(GameState::FADEIN);
			}
			break;
		case GameState::FADEIN:
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			}
			break;
		default:
			break;
		}
	}

	void GameStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}

	void GameStage::ItemGeneration() {
		auto m_countDown = GetSharedGameObject<CountDown>(L"ForCountDown");
		auto flg = (int)m_countDown->GetTime() % 3 == 0;
		if (flg && !m_bOnceItem) {
			m_itemCreation->SpawnInRandPosition();
			m_bOnceItem = true;
		}
		if (!flg) {
			m_bOnceItem = false;
		}
	}

	void GameStage::ChangeGameState(GameState state) {
		m_gameState = state;
	}

	GameStage::GameState GameStage::GetCurrentGameState() {
		return m_gameState;
	}

	void GameStage::Remaining30Sec() {
		SoundManager::GetInstance()->Stop(L"Game1BGM");
		SoundManager::GetInstance()->Play(L"GameLastSpurtBGM");
		SoundManager::GetInstance()->Play(L"WarningSE");

		const int count[4] = {
			0,5,10,20
		};

		auto sortedPlayers = PlayerManager::GetInstance()->GetSortedAllPlayer();
		int index = 0;
		for (auto player : sortedPlayers) {
			player->AddBombCountForRemain30(count[index]);
			index++;
		}

		//auto statusUp = AddGameObject<SimpleSprite>(L"StatusUp");
		//statusUp->AddComponent<FadeComponent>()->SetFadeRange(0.5f, 0);
		//statusUp->GetTransform()->SetPosition(Vec3(0, 300, 0));
	}
}