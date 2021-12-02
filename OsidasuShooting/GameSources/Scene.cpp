/*!
@file Scene.cpp
@brief �V�[������
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
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//�N���A����F��ݒ�
			Col4 Col(30.0f, 30.0f, 30.0f, 1.0f);
			SetClearColor(Utility::ConvertColorZeroToOne(Col));

			const auto& app = App::GetApp();

			auto dir = app->GetDataDirWString();
			// CSV�t�@�C��
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"test", path + L"StringSprite.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			// ���f��
			path = dir + L"Models/";
			auto modelMesh = MultiMeshResource::CreateStaticModelMultiMesh(path + L"LaserCharacter/", L"Laser.bmf");
			app->RegisterResource(L"Player", modelMesh);

			// ���ʉ�
			path = dir + L"Sound/SE/";
			app->RegisterWav(L"Shot", path + L"Shot.wav");
			app->RegisterWav(L"Explosion", path + L"Explosion.wav");
			app->RegisterWav(L"Fall", path + L"Fall.wav");
			app->RegisterWav(L"Jump", path + L"Jump.wav");
			// ���ݖ��g�p
			app->RegisterWav(L"Warning", path + L"Warning.wav");

			// BGM
			path = dir + L"Sound/BGM/";
			app->RegisterWav(L"GameBGM", path + L"Game.wav");

			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
		// �f�o�b�O�X�e�[�W
		if (event->m_MsgStr == L"ToDebugStage") {
			ResetActiveStage<DebugStage>();
		}
		// �^�C�g���X�e�[�W
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		// �L�����N�^�[�Z���N�g�X�e�[�W
		else if (event->m_MsgStr == L"ToCharacterSelectStage") {
			ResetActiveStage<CharacterSelectStage>();
		}
		// �Q�[���X�e�[�W
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		// ���U���g�X�e�[�W
		else if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		// �I��
		else if (event->m_MsgStr == L"ToExit") {
			PostQuitMessage(0);
		}

		// �ȉ�����p�X�e�[�W
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