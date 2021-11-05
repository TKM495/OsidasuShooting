#include "stdafx.h"
#include "Component/PhysicalBehavior.h"

namespace basecross {
	void PhysicalBehavior::OnCreate() {
	}
	void PhysicalBehavior::OnUpdate() {
		// �d�͏���
		Gravity::OnUpdate();
		auto transComp = GetGameObject()->GetComponent<Transform>();
		//�O��̃^�[������̎���
		float delta = App::GetApp()->GetElapsedTime();
		auto pos = transComp->GetPosition();
		pos += m_velocity * delta;
		//m_velocity *= m_frictionFactor;
		m_velocity = Vec3(0.0f);
		transComp->SetPosition(pos);
	}

	void PhysicalBehavior::Move(Vec3 acceleration) {
		float delta = App::GetApp()->GetElapsedTime();
		m_velocity += acceleration;// *delta;
	}

	void PhysicalBehavior::AddForce(Vec3 force) {
	}
}