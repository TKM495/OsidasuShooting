/*!
@file   DebugStage.h
@brief  各種ステージに遷移できるデバッグ用のステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class DebugStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		DebugStage() :Stage() {}
		virtual ~DebugStage() {}
		//初期化
		virtual void OnCreate()override;
		void OnUpdate()override;
	};
}