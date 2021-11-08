/*!
@file DebugCamera.h
@brief ���C���J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class DebugCamera :public Camera {
		float angleRadY; //�J�����̉�荞�݊p�x(���W�A��)
		float length; //�J�����̒����_����̋���
	public:
		DebugCamera()
			:angleRadY(XMConvertToRadians(-90)), length(15.0f)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		//�J�����̉�荞�݂����W�A���p�Ŏ擾����
		float GetAngleRadY() const {
			return angleRadY;
		}
	};
}

//end basecross