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

		bool m_sceneChangeBlock;
	public:
		TitleStage() :Stage(), 
			m_sceneChangeBlock(false)
		{}
		~TitleStage() {}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};
}
