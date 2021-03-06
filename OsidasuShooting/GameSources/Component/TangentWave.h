#pragma once
#include "stdafx.h"

namespace basecross {
	class TangentWave :public Component {
		// 合計時間
		float m_totalTime = 0.0f;
		// 移動方向
		Vec3 m_moveDirection = Vec3();
		// 基準位置
		Vec3 m_basePosition = Vec3();
		// 動きの大きさ
		float m_motionSize = 2000.0f;
		// 時間の倍率
		float m_timeRate = 1.0f;
	public:
		TangentWave(const shared_ptr<GameObject>& gameObjectPtr,
			float startOffset);

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override {}

		void SetMoveDirection(const Vec3 direction);
		void SetMotionSize(float size);
		void SetTimeRate(float rate);

		Vec3 GetMoveDirection();
		float GetMotionSize();
		float GetTimeRate();
	};
}
