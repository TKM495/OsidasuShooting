/*!
@file CameraTester.h
@brief カメラのテストのターゲット
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	// 追跡の対象
	class TargetObj : public GameObject {
	public:
		TargetObj(const shared_ptr<Stage>& stage);
		virtual ~TargetObj() {};
		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross