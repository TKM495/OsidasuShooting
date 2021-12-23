/*!
@file   PhysicalBehavior.cpp
@brief  �����I�ȋ������s���R���|�[�l���g�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PhysicalBehavior::OnCreate() {
		m_groundingDecision.reset(new GroundingDecision(GetGameObject()->GetComponent<Transform>()->GetScale()));
		m_groundingDecision->AddNotDecisionTag(L"Bomb");
		m_groundingDecision->AddNotDecisionTag(L"Bullet");
	}
	void PhysicalBehavior::OnUpdate() {
		// �g�����X�t�H�[���R���|�[�l���g�̎擾
		auto transComp = GetGameObject()->GetComponent<Transform>();
		// �O��̃^�[������̎��Ԃ��擾
		float delta = App::GetApp()->GetElapsedTime();
		// ���݂̈ʒu�ɑ��x����������
		auto pos = transComp->GetPosition();
		pos += m_velocity * delta;
		transComp->SetPosition(pos);

		// �ڒn���Ă���ꍇ�͒n�ʂ̒�R�F�t�͋�C�̒�R���g�p
		auto drag = m_groundingDecision->Calculate(pos) ? m_groundDrag : m_airDrag;

		// �ړ������̋t�ɒ�R�́i���C�Ȃǁj��������
		m_velocity += -m_velocity * drag * delta;

		// ���ʂȌv�Z��h�����߂������l�ȉ���0�Ƃ݂Ȃ�
		if (m_velocity.lengthSqr() < m_threshold * m_threshold)
			m_velocity = Vec3(0.0f);

		// ���݂̑��x���ő呬�x���傫���ꍇ�̓N�����v����
		if (m_velocity.lengthSqr() > m_maxSpeed * m_maxSpeed)
			m_velocity = Utility::ChangeVectorLength(m_velocity, m_maxSpeed);
	}

	void PhysicalBehavior::Move(const Vec3& force) {
		float delta = App::GetApp()->GetElapsedTime();
		m_velocity += force * delta;
	}

	void PhysicalBehavior::Move(const Vec3& direction, float force) {
		// ������const�Ȃ̂ň�U���[�J���̕ϐ���錾
		auto _direction = direction;
		Move(_direction.normalize() * force);
	}

	void PhysicalBehavior::Impact(const Vec3& force) {
		m_velocity += force;
	}

	void PhysicalBehavior::Impact(const Vec3& direction, float force) {
		// ������const�Ȃ̂ň�U���[�J���̕ϐ���錾
		auto _direction = direction;
		Impact(_direction.normalize() * force);
	}
}