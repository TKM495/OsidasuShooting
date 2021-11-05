/*!
@file   PhysicalBehavior.cpp
@brief  物理的な挙動を行うコンポーネントクラスの実体
*/

#include "stdafx.h"
#include "Component/PhysicalBehavior.h"

namespace basecross {
	void PhysicalBehavior::OnUpdate() {
		// トランスフォームコンポーネントの取得
		auto transComp = GetGameObject()->GetComponent<Transform>();
		// 前回のターンからの時間を取得
		float delta = App::GetApp()->GetElapsedTime();
		// 現在の位置に速度分を加える
		auto pos = transComp->GetPosition();
		pos += m_velocity * delta;
		transComp->SetPosition(pos);

		// 移動方向の逆に抵抗力（摩擦など）を加える
		m_velocity += -m_velocity * m_drag * delta;

		// 無駄な計算を防ぐためしきい値以下は0とみなす
		if (m_velocity.lengthSqr() < m_threshold * m_threshold)
			m_velocity = Vec3(0.0f);
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
}