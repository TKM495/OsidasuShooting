#pragma once
#include "stdafx.h"

namespace basecross {
	class TangentWave :public Component {
		// ���v����
		float m_totalTime = 0.0f;
		// �ړ�����
		Vec3 m_moveDirection = Vec3();
		// ��ʒu
		Vec3 m_basePosition = Vec3();
		// �����̑傫��
		float m_motionSize = 2000.0f;
		// ���Ԃ̔{��
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
