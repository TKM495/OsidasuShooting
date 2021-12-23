/*!
@file   PhysicalBehavior.cpp
@brief  物理的な挙動を行うコンポーネントクラスの実体
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
		// トランスフォームコンポーネントの取得
		auto transComp = GetGameObject()->GetComponent<Transform>();
		// 前回のターンからの時間を取得
		float delta = App::GetApp()->GetElapsedTime();
		// 現在の位置に速度分を加える
		auto pos = transComp->GetPosition();
		pos += m_velocity * delta;
		transComp->SetPosition(pos);

		// 接地している場合は地面の抵抗：逆は空気の抵抗を使用
		auto drag = m_groundingDecision->Calculate(pos) ? m_groundDrag : m_airDrag;

		// 移動方向の逆に抵抗力（摩擦など）を加える
		m_velocity += -m_velocity * drag * delta;

		// 無駄な計算を防ぐためしきい値以下は0とみなす
		if (m_velocity.lengthSqr() < m_threshold * m_threshold)
			m_velocity = Vec3(0.0f);

		// 現在の速度が最大速度より大きい場合はクランプする
		if (m_velocity.lengthSqr() > m_maxSpeed * m_maxSpeed)
			m_velocity = Utility::ChangeVectorLength(m_velocity, m_maxSpeed);
	}

	void PhysicalBehavior::Move(const Vec3& force) {
		float delta = App::GetApp()->GetElapsedTime();
		m_velocity += force * delta;
	}

	void PhysicalBehavior::Move(const Vec3& direction, float force) {
		// 引数はconstなので一旦ローカルの変数を宣言
		auto _direction = direction;
		Move(_direction.normalize() * force);
	}

	void PhysicalBehavior::Impact(const Vec3& force) {
		m_velocity += force;
	}

	void PhysicalBehavior::Impact(const Vec3& direction, float force) {
		// 引数はconstなので一旦ローカルの変数を宣言
		auto _direction = direction;
		Impact(_direction.normalize() * force);
	}
}