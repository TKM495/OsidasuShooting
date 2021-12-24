/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 25.0f, -30.0f);
		const Vec3 at(0.0f, 0.0f, -7.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : GameStage");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			GameObjecttCSVBuilder builder;
			builder.Register<Block>(L"Block");
			builder.Register<Bumper>(L"Bumper");
			builder.Register<PlayerBuilder>(L"Player");
			builder.Register<FallDecision>(L"FallDecision");
			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/Stage/";
			builder.Build(GetThis<Stage>(), path + L"StageBase.csv");
			builder.Build(GetThis<Stage>(), path + L"Stage1.csv");

			AddGameObject<CurrentFirst>();
			AddGameObject<modifiedClass::Area>(TransformData(Vec3(0, 0, -6), Vec3(27, 1, 21)));

			m_countDown = AddGameObject<modifiedClass::CountDown>(90.0f);
			m_startCountDown = AddGameObject<StartCountDown>(TransformData());
			m_itemCreation = AddGameObject<modifiedClass::ItemCreation>();

			AddGameObject<TransitionSprite>()->FadeOut();
			SoundManager::GetInstance()->PlayLoop(L"Game1BGM");
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		switch (m_gameState)
		{
		case GameState::FADEOUT:
			// �t�F�[�h���I��������
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
				ChangeGameState(GameState::STAY);
			}
			break;
		case GameState::STAY:
			if (m_startCountDown->GetTimer().IsTimeUp()) {
				m_countDown->Start();
				Debug::GetInstance()->Log(L"GameStart�I�I�I�I�I");
				ChangeGameState(GameState::PLAYING);
			}
			break;
		case GameState::PLAYING:
			// �A�C�e���̐���
			ItemGeneration();
			if (m_countDown->GetTime() <= 0.0f) {
				m_countDown->Stop();
				m_utilTimer.Reset(2.0f);
				AddGameObject<FinishSprite>(TransformData());
				Debug::GetInstance()->Log(L"Finish!!!!!!");
				ChangeGameState(GameState::CLEAR);
			}
			break;
		case GameState::CLEAR:
			if (m_utilTimer.Count()) {
				TransitionSprite::GetInstance()->FadeIn();
				ChangeGameState(GameState::FADEIN);
			}
			break;
		case GameState::FADEIN:
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			}
			break;
		default:
			break;
		}
	}

	void GameStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}

	void GameStage::ItemGeneration() {
		auto flg = (int)m_countDown->GetTime() % 5 == 0;
		if (flg && !m_bOnceItem) {
			m_itemCreation->RandomlySpawn();
			m_bOnceItem = true;
		}
		if (!flg) {
			m_bOnceItem = false;
		}
	}

	void GameStage::ChangeGameState(GameState state) {
		m_gameState = state;
	}

	GameStage::GameState GameStage::GetCurrentGameState() {
		return m_gameState;
	}
}