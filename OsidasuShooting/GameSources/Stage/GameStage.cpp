/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameStage::CreateViewLight() {
		auto line = CSVLoad::GetInstance()->GetData(L"Camera");
		auto data = DataExtracter::DelimitData(line[1]);
		const Vec3 eye = Vec3(
			(float)_wtof(data[1].c_str()),
			(float)_wtof(data[2].c_str()),
			(float)_wtof(data[3].c_str())
		);
		const Vec3 at = Vec3(
			(float)_wtof(data[4].c_str()),
			(float)_wtof(data[5].c_str()),
			(float)_wtof(data[6].c_str())
		);
		//const Vec3 eye(0.0f, 25.0f, -30.0f);
		//const Vec3 at(0.0f, 0.0f, -7.0f);
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
			builder.Register<MoveBlock>(L"MovingBlock");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/";
			builder.Build(GetThis<Stage>(), path + L"StageBase.csv");
			builder.Build(GetThis<Stage>(), path + L"Stage1.csv");

			AddGameObject<CurrentFirst>();
			AddGameObject<modifiedClass::Area>(TransformData(Vec3(0, 0, -6), Vec3(27, 1, 21)));

			m_countDown = AddGameObject<modifiedClass::CountDown>(90.0f);
			m_startCountDown = AddGameObject<StartCountDown>(TransformData());
			m_itemCreation = AddGameObject<modifiedClass::ItemCreation>();

			AddGameObject<TransitionSprite>()->FadeOut();
			SoundManager::GetInstance()->PlayLoop(L"Game1BGM");

			//AddGameObject<ReflectorBlock>(TransformData(Vec3(0,1,-5), Vec3(2)));
			//AddGameObject<BreakBlock>(TransformData(Vec3(0,1,2), Vec3(2)),5,3);
			//AddGameObject<MoveBlock>(TransformData(Vec3(5, 1, -4), Vec3(2)),Vec3(-9,1,-8));
			//AddGameObject<MoveBlock>(TransformData(Vec3(-13, 1, -4), Vec3(2)),Vec3(13,1,-8));
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		switch (m_gameState)
		{
		case GameState::FADEOUT:
			// フェードが終了したら
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
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
			if (m_countDown->GetTime() <= 0.0f) {
				m_countDown->Stop();
				m_utilTimer.Reset(2.0f);
				AddGameObject<FinishSprite>(TransformData());
				Debug::GetInstance()->Log(L"Finish!!!!!!");
				ChangeGameState(GameState::CLEAR);
			}
			break;
		case GameState::CLEAR:
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
		auto flg = (int)m_countDown->GetTime() % 5 == 0;
		if (flg && !m_bOnceItem) {
			m_itemCreation->RandomlySpawn();
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
}