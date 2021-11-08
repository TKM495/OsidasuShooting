#pragma once
#include "stdafx.h"

namespace basecross {

	class JonyStage : public Stage {

		// カメラとライト関連
		void CreateViewLight();

	public:
		JonyStage() :Stage() {}

		virtual ~JonyStage() {}

//override Funtions
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
//override Funtions...end


		// 違うステージに切り替える
		void ChangeToAnotherStage();
	};
}