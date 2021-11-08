#include "stdafx.h"
#include "Project.h"

#include "windows.h"

namespace basecross {
	void JonyStage::CreateViewLight() {

//カメラ関連
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
//カメラ関連...end


//ライト関連
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
//ライト関連...end
	}

	void JonyStage::OnCreate() {
		try {			
			CreateViewLight();// カメラとライト関連

			//テクスチャの読み込み
			//テクスチャの読み込み...end

			//違うゲームオブジェクトを追加

			//空っぽゲームオブジェクト
			auto listsOfVariable = AddGameObject<ListsOfVariable>();
				SetSharedGameObject(L"ListsOfVariable", listsOfVariable);
			//空っぽゲームオブジェクト...end


			//AddGameObject<Debug>();

			AddGameObject<Target>();
			auto obstacles = AddGameObject<Obstacles>();
				SetSharedGameObject(L"Obstacles", obstacles);

			auto obstacles2 = AddGameObject<Obstacles2>();
			SetSharedGameObject(L"Obstacles2", obstacles2);
			obstacles2->AddTag(L"Destroied By Target");
			//違うゲームオブジェクトを追加...end
		}
		catch (...) {
			throw;
		}
	}

	void JonyStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_LBUTTON])
		{
			ChangeToAnotherStage();
		}
	}

	// ゲームステージへの切り替え
	void JonyStage::ChangeToAnotherStage()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}

}