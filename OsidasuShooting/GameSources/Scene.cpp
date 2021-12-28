/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//�N���A����F��ݒ�
			Col4 Col(30.0f, 30.0f, 30.0f, 1.0f);
			SetClearColor(Utility::ConvertColorZeroToOne(Col));

			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToLoadStage");
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
		else if (event->m_MsgStr == L"ToLoadStage") {
			ResetActiveStage<LoadStage>();
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
			ResetActiveStage<WatanabeStage>();
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