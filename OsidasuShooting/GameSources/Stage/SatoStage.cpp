/*!
@file   SatoStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SatoStage::CreateViewLight() {
		//const Vec3 eye(0.0f, 30.0f, -25.0f);
		const Vec3 eye(0.0f, 0.0f, -4.0f);
		//const Vec3 at(0.0f, 0.0f, -2.0f);
		const Vec3 at(0.5f, 0.0f, -2.0f);
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

	//void SatoStage::SetPlayer()
	//{
	//	auto player = AddGameObject<Player>(TransformData());
	//	SetSharedGameObject(L"Player", player);
	//	AddGameObject<Block>(TransformData(Vec3(0.0f, -1.5f, 0.0f), Vec3(10.0f, 1.0f, 10.0f)));

	//}

	void SatoStage::BattlePlayerUISet(int value) {
		auto setNum = 0;
		//auto playerCirecle = AddGameObject<BattlePlayersUIs>(L"BPsUIs",0);
		//auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs",value,Vec3(0));
		
	}

	void SatoStage::AddWinnerSprite()
	{
		auto winnerUIs = AddGameObject<ResultWinnerSprite>(L"Winner");
		auto winnerUIsTrans = winnerUIs->GetComponent<Transform>();
		auto winnerUIsPos = winnerUIsTrans->GetPosition();

		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", 1,Vec3(0));
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		playUIsTrans->SetPosition(winnerUIsPos - Vec3(-412.0f,-27.0f,0));
		playUIsTrans->SetScale(Vec3(1.1f));

	}

	void SatoStage::AddResultSprites(Vec3 pos, int playerNum,int score)
	{
		auto fream = AddGameObject<FreamSprite>(L"Fream");
		auto freamTrans = fream->GetComponent<Transform>();
		auto freamPos = freamTrans->GetPosition();
		auto resultPos = freamPos + pos;
		freamTrans->SetPosition(resultPos);

		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", playerNum, Vec3(0));
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		resultPos.y -= 50.0f;
		playUIsTrans->SetPosition(resultPos);
		playUIsTrans->SetScale(Vec3(0.4f));

		resultPos.x += 120.0f;
		resultPos.y += 25.0f;
		m_score = AddGameObject<ResultScore>(score, resultPos);
		m_score->SetDrawLayer(1);
	}


	void SatoStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring TestEffectStr = DataDir + L"Effects\\";
			EfkEffectResource::RegisterEffectResource(L"Bullet", TestEffectStr + L"Bullet.efk");

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : SatoStage");

			//SetPlayer();

			//AddGameObject<SpecialCamera>();
			
			//// Timer
			//m_timer = AddGameObject<CountDown>();
			//SetSharedGameObject(L"CountDown", m_timer);


			//AddGameObject<Number>(10);

			//BattlePlayerUISet(6);
			
			auto Player1 =  AddGameObject<ManualPlayer>(TransformData(Vec3(0), Vec3(1), Vec3(0,0,1)), PlayerNumber::P1);
			Player1->GetComponent<Gravity>()->SetGravityZero();
			auto PlayerPos = Player1->GetComponent<Transform>()->GetPosition();
			
			auto Laser = AddGameObject<SpecialLaser>(Player1, Vec3(0,0,0), Vec3(0, 0, 0));

			AddGameObject<Block>(TransformData(Vec3(0,-1,0),Vec3(100,1,100)));
			//auto LaserPos->GetPositino();
			//LaserPos.z *= -1;
			//Laser->GetTransform()->SetPosition(LaserPos);
			//

			AddWinnerSprite();

			float addVec = 0;
			float setPosY = 0;
			auto playNum = 0;
			for (int i = 0; i < 4; i++) {
				addVec += 15;
				playNum += 1;
				AddResultSprites(Vec3(390 + addVec, 260 + setPosY,0),playNum,2);
				setPosY -= 160;
			}

		}
		catch (...) {
			throw;
		}
	}

	void SatoStage::OnUpdate() {
		try 
		{
			JMDSeitchSystem();
		}
		catch (...)
		{
			throw;
		}
	}
}