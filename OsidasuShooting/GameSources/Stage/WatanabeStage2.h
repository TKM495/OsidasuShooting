/*!
@file   WatanabeStage2.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WatanabeStage2 : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		WatanabeStage2() :Stage() {}
		virtual ~WatanabeStage2() {}
		//初期化
		virtual void OnCreate()override;
		void OnUpdate()override;
	};
}
