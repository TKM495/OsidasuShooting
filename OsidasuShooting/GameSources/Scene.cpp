/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Scene::GetAppTexture()
	{
		auto& app = App::GetApp();

		wstring tpath = app->GetDataDirWString() + L"Sprite/";

		app->RegisterTexture(L"Title", tpath + L"Title.png");
		app->RegisterTexture(L"PushAButton", tpath + L"PushAButton.png");

		app->RegisterTexture(L"Number", tpath + L"Number.png");
		app->RegisterTexture(L"BPsUIs", tpath + L"BattlePlayersUI256x256.png");
		app->RegisterTexture(L"CircleGauge", tpath + L"CircleGauge.png");
		app->RegisterTexture(L"BarGauge", tpath + L"BarGauge.png");
		app->RegisterTexture(L"GaugeColor", tpath + L"GaugeColor.png");
		app->RegisterTexture(L"Wall", tpath + L"wall.jpg");
		app->RegisterTexture(L"Block", tpath + L"Block.png");
		app->RegisterTexture(L"Test", tpath + L"test.png");

		app->RegisterTexture(L"Winner", tpath + L"Winner.png");
		app->RegisterTexture(L"ResultFream", tpath + L"ResultFream.png");
		app->RegisterTexture(L"BombBack", tpath + L"BombBackGround.png");
		app->RegisterTexture(L"GaugeBackGround", tpath + L"GaugeBackGround.png");
		app->RegisterTexture(L"Gauge", tpath + L"Gauge.png");
		app->RegisterTexture(L"Start", tpath + L"TestStart.png");
		app->RegisterTexture(L"Finish", tpath + L"TestFinish.png");
	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//クリアする色を設定
			Col4 Col(30.0f, 30.0f, 30.0f, 1.0f);
			SetClearColor(Utility::ConvertColorZeroToOne(Col));

			const auto& app = App::GetApp();

			auto dir = app->GetDataDirWString();
			// CSVファイル
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"test", path + L"StringSprite.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			// モデル
			path = dir + L"Models/";
			auto modelMesh = MultiMeshResource::CreateStaticModelMultiMesh(path + L"LaserCharacter/", L"Laser.bmf");
			app->RegisterResource(L"Player", modelMesh);

			// 効果音
			path = dir + L"Sound/SE/";
			app->RegisterWav(L"Shot", path + L"Shot.wav");
			app->RegisterWav(L"Explosion", path + L"Explosion.wav");
			app->RegisterWav(L"Fall", path + L"Fall.wav");
			app->RegisterWav(L"Jump", path + L"Jump.wav");
			// 現在未使用
			app->RegisterWav(L"Warning", path + L"Warning.wav");

			// BGM
			path = dir + L"Sound/BGM/";
			app->RegisterWav(L"GameBGM", path + L"Game.wav");

			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToDebugStage");
			GetAppTexture();
		}
		catch (...) {
			throw;
		}
	}

	Scene::Scene() : SceneBase(),
		m_circleShadowDirection(Vec3(0.3f, -1.0f, 0.3f).normalize())
	{}
	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		// デバッグステージ
		if (event->m_MsgStr == L"ToDebugStage") {
			ResetActiveStage<DebugStage>();
		}
		// タイトルステージ
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		// キャラクターセレクトステージ
		else if (event->m_MsgStr == L"ToCharacterSelectStage") {
			ResetActiveStage<CharacterSelectStage>();
		}
		// ゲームステージ
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		// リザルトステージ
		else if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		// 終了
		else if (event->m_MsgStr == L"ToExit") {
			PostQuitMessage(0);
		}

		// 以下制作用ステージ
		else if (event->m_MsgStr == L"ToWatanabeStage") {
			ResetActiveStage<WatanabeStage2>();
		}
		else if (event->m_MsgStr == L"ToSatoStage") {
			ResetActiveStage<SatoStage>();
		}
		else if (event->m_MsgStr == L"ToJONYMDStage") {
			ResetActiveStage<JONYMDStage>();
		}
	}
}
//end basecross