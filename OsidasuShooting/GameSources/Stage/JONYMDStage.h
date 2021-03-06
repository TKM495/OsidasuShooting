/*!
@file   JONYMDStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class JONYMDStage : public Stage {

		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		JONYMDStage() :Stage() {}
		virtual ~JONYMDStage() {}
		//初期化
		void OnCreate() override;
		void OnUpdate() override;
		void CreateStageArea();

	};
}
