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
			Col4 Col(0.0f, 0.0f, 0.0f, 1.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToDebugStage");
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
		// �Q�[���X�e�[�W
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToWatanabeStage") {
			ResetActiveStage<WatanabeStage>();
		}
		else if (event->m_MsgStr == L"ToSatoStage") {
			ResetActiveStage<SatoStage>();
		}
		else if (event->m_MsgStr == L"ToJONYMDStage") {
			ResetActiveStage<JONYMDStage>();
		}
		//�Q�[���I��
		else if (event->m_MsgStr == L"ToExit") {
			PostQuitMessage(0);
		}
	}
}
//end basecross