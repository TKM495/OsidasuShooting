/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkInterface.h"

namespace basecross {
	class GameStage : public Stage {
		// ビューの作成
		void CreateViewLight();
	public:
		GameStage() :Stage() {}
		~GameStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
