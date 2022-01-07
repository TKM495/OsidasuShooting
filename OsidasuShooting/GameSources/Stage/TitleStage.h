/*!
@file   TitleStage.h
@brief  タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage :public Stage {
		// ビューの作成
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
