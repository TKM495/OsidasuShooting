#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TangentWave::SetMoveDirection(const Vec3 direction) { m_moveDirection = direction; }
	void TangentWave::SetMotionSize(float size) { m_motionSize = size; }
	void TangentWave::SetTimeRate(float rate) { m_timeRate = rate; }

	Vec3 TangentWave::GetMoveDirection() { return m_moveDirection; }
	float TangentWave::GetMotionSize() { return m_motionSize; }
	float TangentWave::GetTimeRate() { return m_timeRate; }

	TangentWave::TangentWave(const shared_ptr<GameObject>& gameObjectPtr,
		float startOffset)
		:Component(gameObjectPtr), m_totalTime(startOffset)
	{}

	void TangentWave::OnCreate() {
		m_basePosition = GetGameObject()->GetComponent<Transform>()->GetPosition();
	}

	void TangentWave::OnUpdate() {
		auto trans = GetGameObject()->GetComponent<Transform>();
		auto t = XMConvertToRadians(tanf(m_totalTime)) * m_motionSize;
		auto pos = m_moveDirection.normalize() * t;
		trans->SetPosition(m_basePosition + pos);
		m_totalTime += App::GetApp()->GetElapsedTime() * m_timeRate;
	}
}