/*!
@file LoadStage.cpp
@brief ロードステージの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	bool LoadStage::m_Loaded = false;
	mutex LoadStage::mtx;

	void LoadStage::LoadResourceFunc() {
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		// リソース読み込み
		const auto& app = App::GetApp();
		auto dir = app->GetDataDirWString();

		// スプライト
		auto path = dir + L"Sprite/";

		app->RegisterTexture(L"AButton", path + L"AButton.png");
		app->RegisterTexture(L"BButton", path + L"BButton.png");
		app->RegisterTexture(L"Cancel", path + L"Cancel.png");
		app->RegisterTexture(L"Decision", path + L"Decision.png");
		app->RegisterTexture(L"Fream", path + L"Fream.png");
		app->RegisterTexture(L"OK", path + L"OK.png");
		app->RegisterTexture(L"PushAButton", path + L"PushAButton.png");

		app->RegisterTexture(L"3WayIcon", path + L"3WayIcon.png");
		app->RegisterTexture(L"LaserIcon", path + L"LaserIcon.png");
		app->RegisterTexture(L"MissileIcon", path + L"MissileIcon.png");

		app->RegisterTexture(L"CharacterSelect", path + L"CharacterSelect.png");
		app->RegisterTexture(L"ReTriangle", path + L"ReTriangle.png");
		app->RegisterTexture(L"Triangle", path + L"Triangle.png");

		app->RegisterTexture(L"ReadyToFight", path + L"ReadyToFight.png");

		app->RegisterTexture(L"Winner", path + L"Winner.png");
		app->RegisterTexture(L"BombBack", path + L"BombBackGround.png");
		app->RegisterTexture(L"GaugeBackGround", path + L"GaugeBackGround.png");
		app->RegisterTexture(L"Gauge", path + L"Gauge.png");

		app->RegisterTexture(L"Title", path + L"Title.png");
		app->RegisterTexture(L"PushAButton", path + L"PushAButton.png");
		app->RegisterTexture(L"Number", path + L"Number.png");
		app->RegisterTexture(L"BPsUIs", path + L"BattlePlayersUI256x256.png");
		app->RegisterTexture(L"CircleGauge", path + L"CircleGauge.png");
		app->RegisterTexture(L"BarGauge", path + L"BarGauge.png");
		app->RegisterTexture(L"GaugeColor", path + L"GaugeColor.png");
		app->RegisterTexture(L"Wall", path + L"wall.jpg");
		app->RegisterTexture(L"Block", path + L"Block.png");
		app->RegisterTexture(L"Test", path + L"test.png");
		app->RegisterTexture(L"Winner", path + L"Winner.png");

		app->RegisterTexture(L"BombBack", path + L"BombBackGround.png");
		app->RegisterTexture(L"GaugeBackGround", path + L"GaugeBackGround.png");

		app->RegisterTexture(L"Gauge", path + L"Gauge.png");
		app->RegisterTexture(L"Start", path + L"Fight.png");
		app->RegisterTexture(L"Finish", path + L"Finish.png");
		app->RegisterTexture(L"BackGround00", path + L"BackGround00.png");

		// CSVファイル
		path = dir + L"CSV/";
		CSVLoad::GetInstance()->RegisterFile(L"test", path + L"StringSprite.csv");
		CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
		CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

		//XMLファイル
		path = dir + L"XML/";
		XMLLoad::GetInstance()->RegisterFile(L"PlayerStatus", path + L"PlayerStatus.xml");

		// モデル
		path = dir + L"Models/LaserCharacter/";
		for (int i = 0; i < 4; i++) {
			auto number = Util::IntToWStr(i + 1);
			auto modelMesh = MultiMeshResource::CreateStaticModelMultiMesh(path + L"Player" + number + L"/", L"LaserPlayer" + number + L".bmf");
			app->RegisterResource(L"Player" + number, modelMesh);
		}

		// 効果音
		path = dir + L"Sound/SE/";
		app->RegisterWav(L"EmptyBombSE", path + L"EmptyBomb.wav");
		app->RegisterWav(L"DecisionSE", path + L"Decision.wav");
		app->RegisterWav(L"ExplosionSE", path + L"Explosion.wav");
		app->RegisterWav(L"FallSE", path + L"Fall.wav");
		app->RegisterWav(L"HoverSE", path + L"Hover.wav");
		app->RegisterWav(L"JumpSE", path + L"Jump.wav");
		app->RegisterWav(L"ShotSE", path + L"Shot.wav");
		app->RegisterWav(L"ThrowBombSE", path + L"ThrowBomb.wav");
		app->RegisterWav(L"WarningSE", path + L"Warning.wav");

		// BGM
		path = dir + L"Sound/BGM/";
		app->RegisterWav(L"Game1BGM", path + L"Game1.wav");
		app->RegisterWav(L"Game2BGM", path + L"Game2.wav");
		app->RegisterWav(L"ResultBGM", path + L"Result.wav");
		app->RegisterWav(L"SelectBGM", path + L"Select.wav");
		app->RegisterWav(L"TitleBGM", path + L"Title.wav");

		mtx.lock();
		m_Loaded = true;
		mtx.unlock();
	}

	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void LoadStage::OnCreate() {
		auto& app = App::GetApp();
		auto dir = app->GetDataDirWString();
		// スプライト
		auto path = dir + L"Sprite/";
		app->RegisterTexture(L"Loading", path + L"NowLoading.png");

		//他のリソースを読み込むスレッドのスタート
		thread LoadThread(LoadResourceFunc);
		//終了までは待たない
		LoadThread.detach();

		CreateViewLight();
		AddGameObject<Debug>();
		Debug::GetInstance()->Log(L"CurrentStage : LoadStage");

		auto sprite = AddGameObject<SimpleSprite>(L"Loading",
			TransformData(Vec3(350.0f, -300.0f, 0.0f), Vec3(0.7f)));
		AddGameObject<TransitionSprite>();
	}

	void LoadStage::OnUpdate() {
		switch (m_state)
		{
		case State::Loading:
			if (m_Loaded && m_timer.Count()) {
				//リソースのロードが終了&指定の時間が経過したらフェード開始
				TransitionSprite::GetInstance()->FadeIn();
				m_state = State::FadeOut;
				Debug::GetInstance()->Log(L"LoadComplete");
			}
			break;
		case State::FadeOut:
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
				//フェードが完了したらタイトルステージに移行
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToDebugStage");
			}
			break;
		}
	}
}
//end basecross