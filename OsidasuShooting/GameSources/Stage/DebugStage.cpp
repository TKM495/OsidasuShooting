/*!
@file   DebugStage.cpp
@brief  �e��X�e�[�W�ɑJ�ڂł���f�o�b�O�p�̃X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void DebugStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
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

	void DebugStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : DebugStage");
			Debug::GetInstance()->Log(L"W �� WatanabeStage");
			Debug::GetInstance()->Log(L"S �� SatoStage");
			Debug::GetInstance()->Log(L"J �� JONYMDStage");
			Debug::GetInstance()->Log(L"M �� GameStage");
		}
		catch (...) {
			throw;
		}
	}

	void DebugStage::OnUpdate() {
		const auto& app = App::GetApp();
		const auto& keyState = app->GetInputDevice().GetKeyState();
		if (keyState.m_bPressedKeyTbl['W'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToWatanabeStage");
		else if (keyState.m_bPressedKeyTbl['S'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToSatoStage");
		else if (keyState.m_bPressedKeyTbl['J'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToJONYMDStage");
		else if (keyState.m_bPressedKeyTbl['M'])
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
	}
}