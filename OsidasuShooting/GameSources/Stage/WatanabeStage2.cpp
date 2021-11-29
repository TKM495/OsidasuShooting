/*!
@file   WatanabeStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	void WatanabeStage2::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<DebugCamera>(10.0f, 0.0f);
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void WatanabeStage2::OnCreate() {
		try {
			AddGameObject<EfkInterface>();
			auto efkpath = App::GetApp()->GetDataDirWString() + L"Effects/";
			EfkEffectResource::RegisterEffectResource(L"Bullet", efkpath + L"Bullet.efk");
			EfkEffectResource::RegisterEffectResource(L"Explosion", efkpath + L"fire.efk");
			EfkEffectResource::RegisterEffectResource(L"Hit", efkpath + L"Hit.efk");
			EfkEffectResource::RegisterEffectResource(L"Jump", efkpath + L"Jump.efk");
			EfkEffectResource::RegisterEffectResource(L"Hover", efkpath + L"Hover.efk");

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : WatanabeStage2");

			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			//AddGameObject<LinePoint>(TransformData(Vec3(0.0f), Vec3(3.0f)));

			//AddGameObject<Block>(TransformData(Vec3(10.0f, 0.0f, 0.0f)));
			//AddGameObject<Block>(TransformData(Vec3(0.0f, 0.0f, 10.0f)));
			//AddGameObject<Block>(TransformData(Vec3(10.0f, 0.0f, 10.0f)));

			AddGameObject<Block>(TransformData(Vec3(0.0f, -1.0f, 0.0f)));

			auto player = AddGameObject<ManualPlayer>(TransformData(Vec3(0.0f, 2.0f, 0.0f), Vec3(1.0f)), PlayerNumber::P1);
			//AddGameObject<PlayerInfo>(player, TransformData());
			//AddGameObject<PlayerFollowUI>(player, TransformData());
			//AddGameObject<BattlePlayersUIs>(L"BPsUIs", 6, Vec3(0));
			//PlayerManager::GetInstance()->AddPlayer(player);

			//AddGameObject<SimpleSprite>(L"Test", TransformData(Vec3(0.0f), Vec3(0.4f)))->SetDrawLayer(-2);

			//unique_ptr<XmlDocReader> m_XmlDocReader;
			//m_XmlDocReader.reset(new XmlDocReader(dir + L"XML/PlayerStatus.xml"));
			//auto CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"PlayerStatus");
			////内容の文字列を取得
			//wstring MapStr = XmlDocReader::GetText(CellmapNode);
			//vector<wstring> tokens;
			//Util::WStrToTokenVector(tokens, MapStr, L' ');
			//Debug::GetInstance()->Log(tokens[1]);
			AddGameObject<TransitionSprite>()->FadeOut();
		}
		catch (...) {
			throw;
		}
	}

	void WatanabeStage2::OnUpdate() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		const auto& cont = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cont.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bPressedKeyTbl['R'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWatanabeStage");
	}
}