/*!
@file   SatoStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SatoStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -15.0f);
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

	//void SatoStage::SetPlayer()
	//{
	//	auto player = AddGameObject<Player>(TransformData());
	//	SetSharedGameObject(L"Player", player);
	//	AddGameObject<Block>(TransformData(Vec3(0.0f, -1.5f, 0.0f), Vec3(10.0f, 1.0f, 10.0f)));

	//}


	void SatoStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			wstring TestEffectStr = DataDir + L"Effects\\";
			EfkEffectResource::RegisterEffectResource(L"Bullet", TestEffectStr + L"Bullet.efk");

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Debug>();
			Debug::GetInstance()->Log(L"CurrentStage : SatoStage");

			//SetPlayer();

			//AddGameObject<SpecialCamera>();
			AddGameObject<Number>(2);
			m_timer = AddGameObject<CountDown>();
			


		}
		catch (...) {
			throw;
		}
	}
}