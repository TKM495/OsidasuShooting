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
			auto efkpath = App::GetApp()->GetDataDirWString() + L"Effects/";
			EfkEffectResource::RegisterEffectResource(L"Bullet", efkpath + L"Bullet.efk");
			EfkEffectResource::RegisterEffectResource(L"Explosion", efkpath + L"fire.efk");
			EfkEffectResource::RegisterEffectResource(L"Hit", efkpath + L"Hit.efk");
			EfkEffectResource::RegisterEffectResource(L"Jump", efkpath + L"Jump.efk");
			EfkEffectResource::RegisterEffectResource(L"Hover", efkpath + L"Hover.efk");
			EfkEffectResource::RegisterEffectResource(L"Bomb", efkpath + L"Bomb.efk");
			EfkEffectResource::RegisterEffectResource(L"Smoke", efkpath + L"Smoke.efk");
			EfkEffectResource::RegisterEffectResource(L"Laser", efkpath + L"Laser.efk");

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : GameStage");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<PlayerBuilder>(L"Player");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/Stage1";
			path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			AddGameObject<FallDecision>();
			AddGameObject<CurrentFirst>();

			m_countDown = AddGameObject<CountDown>(0.0f);
			m_startCountDown = AddGameObject<StartCountDown>(TransformData());
			AddGameObject<TransitionSprite>()->FadeOut();
			SoundManager::GetInstance()->PlayLoop(L"Game1BGM");
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

	void GameStage::ChangeGameState(GameState state) {
		m_gameState = state;
	}

	GameStage::GameState GameStage::GetCurrentGameState() {
		return m_gameState;
	}
}