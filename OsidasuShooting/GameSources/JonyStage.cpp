#include "stdafx.h"
#include "Project.h"

#include "windows.h"

namespace basecross {
	void JonyStage::CreateViewLight() {

//�J�����֘A
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
//�J�����֘A...end


//���C�g�֘A
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
//���C�g�֘A...end
	}

	void JonyStage::OnCreate() {
		try {			
			CreateViewLight();// �J�����ƃ��C�g�֘A

			//�e�N�X�`���̓ǂݍ���
			//�e�N�X�`���̓ǂݍ���...end

			//�Ⴄ�Q�[���I�u�W�F�N�g��ǉ�

			//����ۃQ�[���I�u�W�F�N�g
			auto listsOfVariable = AddGameObject<ListsOfVariable>();
				SetSharedGameObject(L"ListsOfVariable", listsOfVariable);
			//����ۃQ�[���I�u�W�F�N�g...end


			//AddGameObject<Debug>();

			AddGameObject<Target>();
			auto obstacles = AddGameObject<Obstacles>();
				SetSharedGameObject(L"Obstacles", obstacles);

			auto obstacles2 = AddGameObject<Obstacles2>();
			SetSharedGameObject(L"Obstacles2", obstacles2);
			obstacles2->AddTag(L"Destroied By Target");
			//�Ⴄ�Q�[���I�u�W�F�N�g��ǉ�...end
		}
		catch (...) {
			throw;
		}
	}

	void JonyStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_LBUTTON])
		{
			ChangeToAnotherStage();
		}
	}

	// �Q�[���X�e�[�W�ւ̐؂�ւ�
	void JonyStage::ChangeToAnotherStage()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}

}