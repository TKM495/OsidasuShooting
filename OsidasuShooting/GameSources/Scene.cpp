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
	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//クリアする色を設定
			Col4 Col(0.0f, 0.0f, 0.0f, 1.0f);
			SetClearColor(Col);

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
			ResetActiveStage<WatanabeStage>();
		}
		else if (event->m_MsgStr == L"ToSatoStage") {
			ResetActiveStage<SatoStage>();
		}
		else if (event->m_MsgStr == L"ToJONYMDStage") {
			ResetActiveStage<JONYMDStage>();
		}
		// ゲーム終了
		else if (event->m_MsgStr == L"ToExit") {
			PostQuitMessage(0);
		}
	}
}
//end basecross