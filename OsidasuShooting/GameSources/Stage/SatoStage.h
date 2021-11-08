/*!
@file   SatoStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SatoStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		SatoStage() :Stage() {}
		virtual ~SatoStage() {}
		//初期化

		void SetPlayer();
		virtual void OnCreate()override;
	};
}
