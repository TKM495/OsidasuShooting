/*!
@file   DebugStage.h
@brief  �e��X�e�[�W�ɑJ�ڂł���f�o�b�O�p�̃X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class DebugStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		DebugStage() :Stage() {}
		virtual ~DebugStage() {}
		//������
		virtual void OnCreate()override;
		void OnUpdate()override;
	};
}