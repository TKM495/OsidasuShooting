/*!
@file   PhysicalBehavior.cpp
@brief  �����I�ȋ������s���R���|�[�l���g�N���X�̎���
*/

#include "stdafx.h"
#include "Component/PhysicalBehavior.h"

namespace basecross {
	void PhysicalBehavior::OnUpdate() {
		// �g�����X�t�H�[���R���|�[�l���g�̎擾
		auto transComp = GetGameObject()->GetComponent<Transform>();
		// �O��̃^�[������̎��Ԃ��擾
		float delta = App::GetApp()->GetElapsedTime();
		// ���݂̈ʒu�ɑ��x����������
		auto pos = transComp->GetPosition();
		pos += m_velocity * delta;
		transComp->SetPosition(pos);

		// �ړ������̋t�ɒ�R�́i���C�Ȃǁj��������
		m_velocity += -m_velocity * m_drag * delta;

		// ���ʂȌv�Z��h�����߂������l�ȉ���0�Ƃ݂Ȃ�
		if (m_velocity.lengthSqr() < m_threshold * m_threshold)
			m_velocity = Vec3(0.0f);
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
}