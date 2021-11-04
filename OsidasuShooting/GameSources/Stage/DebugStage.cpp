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
		}
		catch (...) {
			throw;
		}
	}

	void DebugStage::OnUpdate() {
	}
}