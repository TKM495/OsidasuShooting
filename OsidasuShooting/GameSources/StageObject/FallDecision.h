/*!
@file   FallDecision.h
@brief  触れたら落下判定とするオブジェクト
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class FallDecision :public StageObject {
	public:
		FallDecision(const shared_ptr<Stage>& stage)
			:StageObject(stage)
		{
			m_transformData.Position = Vec3(0.0f, -20.0f, 0.0f);
			m_transformData.Scale = Vec3(100.0f, 1.0f, 100.0f);
		}

		void OnCreate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
