/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 25.0f, -30.0f);
		const Vec3 at(0.0f, 0.0f, -7.0f);
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
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring TestEffectStr = DataDir + L"Effects\\";
			EfkEffectResource::RegisterEffectResource(L"Bullet", TestEffectStr + L"Bullet.efk");
			EfkEffectResource::RegisterEffectResource(L"Explosion", TestEffectStr + L"fire.efk");

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : GameStage");

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage";
			path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			auto player = AddGameObject<ManualPlayer>(TransformData(Vec3(10.0f, 1.0f, -15.0f)), PlayerNumber::P1);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(-500.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			player = AddGameObject<ManualPlayer>(TransformData(Vec3(-10.0f, 1.0f, -15.0f)), PlayerNumber::P2);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(-180.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			player = AddGameObject<ManualPlayer>(TransformData(Vec3(10.0f, 1.0f, 0.0f)), PlayerNumber::P3);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(180.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			player = AddGameObject<ManualPlayer>(TransformData(Vec3(-10.0f, 1.0f, 0.0f)), PlayerNumber::P4);
			AddGameObject<PlayerInfo>(player, TransformData(Vec3(500.0f, -250.0f, 0.0f)));
			AddGameObject<PlayerFollowUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);

			AddGameObject<FallDecision>();
			AddGameObject<CurrentFirst>();

			m_countDown = AddGameObject<CountDown>(90.0f);
			AddGameObject<TransitionSprite>()->FadeOut();
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
			if (m_startCountDownTimer.Count()) {
				m_countDown.lock()->Start();
				Debug::GetInstance()->Log(L"GameStart！！！！！");
				ChangeGameState(GameState::PLAYING);
				break;
			}
			Debug::GetInstance()->ClearLog();
			Debug::GetInstance()->Log(m_startCountDownTimer.GetLeftTime() + 1.0f);
			break;
		case GameState::PLAYING:
			if (m_countDown.lock()->GetTime() <= 0.0f)
				ChangeGameState(GameState::CLEAR);
			break;
		case GameState::CLEAR:
			TransitionSprite::GetInstance()->FadeIn();
			ChangeGameState(GameState::FADEIN);
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

	void GameStage::ChangeGameState(GameState state) {
		m_gameState = state;
	}

	GameStage::GameState GameStage::GetCurrentGameState() {
		return m_gameState;
	}
}