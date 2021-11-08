#pragma once
#include "stdafx.h"
#include "StageObject/StageObject.h"

namespace basecross {
	class LinePoint :public StageObject {
	public:
		LinePoint(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage)
		{}

		void OnCreate()override;
	};
}
