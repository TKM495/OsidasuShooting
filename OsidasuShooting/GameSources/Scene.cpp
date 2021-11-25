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
		app->RegisterTexture(L"WhiteLine", tpath + L"White.png");

		app->RegisterTexture(L"Title", tpath + L"Title.png");
		app->RegisterTexture(L"PushAButton", tpath + L"PushAButton.png");

		app->RegisterTexture(L"Number", tpath + L"Number.png");
		app->RegisterTexture(L"BPsUIs", tpath + L"BattlePlayersUI256x256.png");
		app->RegisterTexture(L"CircleGauge", tpath + L"CircleGauge.png");
		app->RegisterTexture(L"BarGauge", tpath + L"BarGauge.png");
		app->RegisterTexture(L"GaugeColor", tpath + L"GaugeColor.png");
		app->RegisterTexture(L"Wall", tpath + L"wall.jpg");
		app->RegisterTexture(L"Test", tpath + L"test.png");

		app->RegisterTexture(L"Winner", tpath + L"Winner.png");
	}

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//�N���A����F��ݒ�
			Col4 Col(0.0f, 0.0f, 0.0f, 1.0f);
			SetClearColor(Col);

			auto dir = App::GetApp()->GetDataDirWString();
			auto path = dir + L"Csv/";
			CSVLoad::GetInstance()->RegisterFile(L"test", path + L"StringSprite.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
			CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");

			//App::GetApp()->SetFullScreenMode();

			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
		// �f�o�b�O�X�e�[�W
		if (event->m_MsgStr == L"ToDebugStage") {
			ResetActiveStage<DebugStage>();
		}
		// �^�C�g���X�e�[�W
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
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