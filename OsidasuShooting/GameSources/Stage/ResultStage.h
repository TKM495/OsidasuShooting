/*!
@file   ResultStage.h
@brief  ���U���g�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ResultStage :public Stage {
		// �r���[�̍쐬
		void CreateViewLight();
	public:
		ResultStage() :Stage() {}
		~ResultStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
