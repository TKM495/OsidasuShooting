/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "TestObject.h"
#include "DebugClass/DebugCamera.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<DebugCamera>();
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
			//ObjectFactory::Create<EfkInterface>(GetThis<GameStage>());
			AddGameObject<EfkInterface>();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring TestEffectStr = DataDir + L"Effects\\test.efk";

			EfkEffectResource::RegisterEffectResource(L"Test", TestEffectStr);

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			AddGameObject<Debug>();

			AddGameObject<TestObject>();

			AddGameObject<Block>(Vec3(0.0f, -1.5f, 0.0f), Vec3(10.0f, 1.0f, 10.0f));
		}
		catch (...) {
			throw;
		}
	}
}
//end basecross