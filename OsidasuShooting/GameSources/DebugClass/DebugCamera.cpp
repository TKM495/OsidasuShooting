#include "stdafx.h"
#include "Project.h"
#include "DebugCamera.h"

namespace basecross {
	void DebugCamera::OnCreate() {
		auto eye = Vec3(cosf(angleRadY), 0.0f, sinf(angleRadY)) * length;
		eye += Vec3(0.0f, 15.0f, 0.0f);
		SetEye(eye);
		SetAt(0.0f, 0.0f, 0.0f);
	}

	void DebugCamera::OnUpdate() {
		auto& app = App::GetApp(); //�A�v���P�[�V�����I�u�W�F�N�g���擾
		auto scene = app->GetScene<Scene>(); //�A�v���P�[�V�����I�u�W�F�N�g����V�[�����擾
		auto stage = scene->GetActiveStage(); //�V�[������X�e�[�W���擾����

		auto delta = app->GetElapsedTime();

		auto device = app->GetInputDevice();

		int i = 0;
		if (device.GetKeyState().m_bPushKeyTbl[VK_LEFT]) {
			i = -1;
		}
		if (device.GetKeyState().m_bPushKeyTbl[VK_RIGHT]) {
			i = 1;
		}

		//�X�e�B�b�N�̌X���ɉ����ăJ��������荞�܂���
		auto deg = i * 90.0f;
		angleRadY += XMConvertToRadians(deg) * delta;

		//�J�����̉�荞�݂̊p�x�Ƌ����ňʒu�����肷��
		auto eye = Vec3(cosf(angleRadY), 0.0f, sinf(angleRadY)) * length;
		eye += Vec3(0.0f, 15.0f, 0.0f);
		SetEye(eye);
	}
}