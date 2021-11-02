/*!
@file   Player.h
@brief  ƒvƒŒƒCƒ„[
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	class Player :public StageObject {
	public:
		Player(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
