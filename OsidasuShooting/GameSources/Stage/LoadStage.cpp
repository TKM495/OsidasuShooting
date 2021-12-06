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

		// ここでリソース読み込み

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

		//他のリソースを読み込むスレッドのスタート
		thread LoadThread(LoadResourceFunc);
		//終了までは待たない
		LoadThread.detach();

		CreateViewLight();

		AddGameObject<TransitionSprite>();
	}

	void LoadStage::OnUpdate() {
		switch (m_state)
		{
		case State::Loading:
			if (m_Loaded && m_timer.Count()) {
				//リソースのロードが終了&指定の時間が経過したらフェード開始
				TransitionSprite::GetInstance()->FadeOut();
				m_state = State::FadeOut;
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