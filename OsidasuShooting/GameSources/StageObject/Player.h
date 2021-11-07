/*!
@file   Player.h
@brief  プレイヤー
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
		// 移動速度（どちらかというとかける力）
		float m_moveSpeed;
	public:
		Player(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage), m_moveSpeed(20.0f)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
