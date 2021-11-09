/*!
@file   TitleStage.h
@brief  �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage :public Stage {
		// �r���[�̍쐬
		void CreateViewLight();
		void AddTitleSprite();
		void AddPushAButtonSprite();
	public:
		TitleStage() :Stage() {}
		~TitleStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}