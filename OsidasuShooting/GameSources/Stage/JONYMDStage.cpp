/*!
@file   JONYMDStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void JONYMDStage::CreateViewLight() {
		const Vec3 eye(0.0f, 25.0f, -30.0f);
		const Vec3 at(0.0f, 0.0f, -7.0f);

		//camera acquisition
		auto view = CreateView<SingleView>();
		auto camera = ObjectFactory::Create<Camera>();
		view->SetCamera(camera);
		camera->SetEye(eye);
		camera->SetAt(at);
		//camera acquisition...end

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void JONYMDStage::OnCreate() {
		try {
			//ビューとライトの作成

			CreateViewLight();
			CreateStageArea();

			//AddGameObject<Debug>();

			//AddGameObject<Fencing>();


			//auto area = AddGameObject<Area>();
			//SetSharedGameObject(L"Area", area);

			auto itemCreation = AddGameObject<ItemCreation>();
			SetSharedGameObject(L"ItemCreation", itemCreation);
			
			//auto meteoriteCreation = AddGameObject<MeteoriteCreation>();
			//SetSharedGameObject(L"MeteoriteCreation", meteoriteCreation);

		}
		catch (...) {
			throw;
		}
	}


	void JONYMDStage::OnUpdate() {
		
		auto& app = App::GetApp();
		auto& keyState = app->GetInputDevice().GetKeyState();

		if (keyState.m_bPressedKeyTbl[VK_SPACE]) 
		{
			auto itemCreation = GetSharedGameObject<ItemCreation>(L"ItemCreation");
			itemCreation->RandomlySpawn();
		}
		
	}

	
	void JONYMDStage::CreateStageArea()
	{
		auto& app = App::GetApp();
		auto dir = app->GetDataDirWString();
		auto pathSprite = dir + L"Sprite/";
		app->RegisterTexture(L"Block", pathSprite + L"Block.png");

		GameObjecttCSVBuilder builder;
		builder.Register<Block>(L"Block");
		auto path = dir + L"Csv/Stage/Stage1_Before";
		path += L".csv";
		builder.Build(GetThis<Stage>(), path);
		
	}

}