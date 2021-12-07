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

		app->RegisterTexture(L"AButton", tpath + L"AButton.png");
		app->RegisterTexture(L"BButton", tpath + L"BButton.png");
		app->RegisterTexture(L"Cancel", tpath + L"Cancel.png");
		app->RegisterTexture(L"Decision", tpath + L"Decision.png");
		app->RegisterTexture(L"Fream", tpath + L"Fream.png");
		app->RegisterTexture(L"OK", tpath + L"OK.png");
		app->RegisterTexture(L"PushAButton", tpath + L"PushAButton.png");
		app->RegisterTexture(L"Title", tpath + L"Title.png");

		app->RegisterTexture(L"3WayIcon", tpath + L"3WayIcon.png");
		app->RegisterTexture(L"LaserIcon", tpath + L"LaserIcon.png");
		app->RegisterTexture(L"MissileIcon", tpath + L"MissileIcon.png");

		app->RegisterTexture(L"CharacterSelect", tpath + L"CharacterSelect.png");
		app->RegisterTexture(L"ReTriangle", tpath + L"ReTriangle.png");
		app->RegisterTexture(L"Triangle", tpath + L"Triangle.png");
		
		app->RegisterTexture(L"ReadyToFight", tpath + L"ReadyToFight.png");

		app->RegisterTexture(L"Number", tpath + L"Number.png");
		app->RegisterTexture(L"BPsUIs", tpath + L"BattlePlayersUI256x256.png");
		app->RegisterTexture(L"CircleGauge", tpath + L"CircleGauge.png");
		app->RegisterTexture(L"BarGauge", tpath + L"BarGauge.png");
		app->RegisterTexture(L"GaugeColor", tpath + L"GaugeColor.png");
		app->RegisterTexture(L"Wall", tpath + L"wall.jpg");
		app->RegisterTexture(L"Test", tpath + L"test.png");

		app->RegisterTexture(L"Winner", tpath + L"Winner.png");
		app->RegisterTexture(L"BombBack", tpath + L"BombBackGround.png");
		app->RegisterTexture(L"GaugeBackGround", tpath + L"GaugeBackGround.png");
		app->RegisterTexture(L"Gauge", tpath + L"Gauge.png");
	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//クリアする色を設定
			Col4 Col(30.0f, 30.0f, 30.0f, 1.0f);
			SetClearColor(Utility::ConvertColorZeroToOne(Col));

			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"test", path + L"StringSprite.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			path = dir + L"Models/";
			auto modelMesh = MultiMeshResource::CreateStaticModelMultiMesh(path + L"LaserCharacter/", L"Laser.bmf");
			App::GetApp()->RegisterResource(L"Player", modelMesh);
			//App::GetApp()->SetFullScreenMode();

			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToDebugStage");
			GetAppTexture();
		}
		catch (...) {
			throw;
		}
	}

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