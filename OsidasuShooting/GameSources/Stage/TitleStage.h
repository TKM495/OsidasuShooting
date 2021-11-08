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
	public:
		TitleStage() :Stage() {}
		~TitleStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
