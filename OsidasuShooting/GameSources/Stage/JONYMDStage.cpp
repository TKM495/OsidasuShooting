/*!
@file   JONYMDStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void JONYMDStage::CreateViewLight() {
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

	void JONYMDStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//AddGameObject<Debug>();
			//Debug::GetInstance()->Log(L"CurrentStage : JONYMDStage");

			auto countDown = AddGameObject<CountDown>();
			SetSharedGameObject(L"CountDown", countDown);

		}
		catch (...) {
			throw;
		}
	}


	void JONYMDStage::OnUpdate() {
		const auto& app = App::GetApp();
		const auto& keyState = app->GetInputDevice().GetKeyState();
		if (keyState.m_bPressedKeyTbl['W']) {
			GetSharedGameObject<CountDown>(L"CountDown")->Start();
		}
		if (keyState.m_bPressedKeyTbl['S']) {
			GetSharedGameObject<CountDown>(L"CountDown")->Stop();
		}
		if (keyState.m_bPressedKeyTbl['R']) {
			GetSharedGameObject<CountDown>(L"CountDown")->Reset();
		}



		if (keyState.m_bPressedKeyTbl['A']) {
			GetSharedGameObject<CountDown>(L"CountDown")->Adjust(5);
		}
		if (keyState.m_bPressedKeyTbl['M']) {
			GetSharedGameObject<CountDown>(L"CountDown")->Adjust(-5);
		}
	}
}