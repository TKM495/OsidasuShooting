/*!
@file   TitleStage.cpp
@brief  タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<TitleCamera>();
		PtrView->SetCamera(PtrCamera);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleStage::AddTitleSprite()
	{
		AddGameObject<TitleSprite>(L"Title"/*, false,
			Vec2(256.0f, 50.0f), Vec2(0.0f, 50.0f)*/);
	}
	void TitleStage::AddPushAButtonSprite()
	{
		AddGameObject<PushAButtonSprite>(L"PushAButton"/*, false,
			Vec2(256.0f, 50.0f), Vec2(0.0f, 50.0f)*/);
	}

	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//AddGameObject<Debug>();
			//Debug::GetInstance()->Log(L"CurrentStage : TitleStage");
			//Debug::GetInstance()->Log(L"A : CharacterSelect");
			//Debug::GetInstance()->Log(L"B : Exit");

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
			builder.Build(GetThis<Stage>(), path + L"TitleStage.csv");
			// 背景
			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			AddTitleSprite();
			AddPushAButtonSprite();
			SoundManager::GetInstance()->PlayLoop(L"TitleBGM");
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];
		// キャラクターセレクトへ
		if (!m_sceneChangeBlock) {
			if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A) {
				SoundManager::GetInstance()->Play(L"DecisionSE");
				PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToCharacterSelectStage");
				m_sceneChangeBlock = true;
			}
			// ゲーム終了
			if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_B) {
				SoundManager::GetInstance()->Play(L"CancelSE");
				PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToExit");
				m_sceneChangeBlock = true;
			}
		}
	}
	void TitleStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}