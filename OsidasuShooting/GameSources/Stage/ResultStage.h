/*!
@file   ResultStage.h
@brief  リザルトステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ResultStage :public Stage {
		// ビューの作成
		void CreateViewLight();
	public:
		ResultStage() :Stage() {}
		~ResultStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
