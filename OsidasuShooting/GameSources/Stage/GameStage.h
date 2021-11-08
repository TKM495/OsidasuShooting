/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkInterface.h"

namespace basecross {
	class GameStage : public Stage {
		// �r���[�̍쐬
		void CreateViewLight();
	public:
		GameStage() :Stage() {}
		~GameStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
