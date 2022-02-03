#pragma once
#include "stdafx.h"

namespace basecross {
	class TangentWave :public Component {
		// ‡ŒvŠÔ
		float m_totalTime = 0.0f;
		// ˆÚ“®•ûŒü
		Vec3 m_moveDirection = Vec3();
		// Šî€ˆÊ’u
		Vec3 m_basePosition = Vec3();
		// “®‚«‚Ì‘å‚«‚³
		float m_motionSize = 2000.0f;
		// ŠÔ‚Ì”{—¦
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
