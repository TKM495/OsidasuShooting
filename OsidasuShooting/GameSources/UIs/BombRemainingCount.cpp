#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BombRemainingCount::OnCreate() {
		m_number = ObjectFactory::Create<Number>(GetStage(), 0);
		auto trans = m_number->GetComponent<Transform>();
		trans->SetPosition(m_transformData.Position);
		trans->SetScale(m_transformData.Scale);
		trans->SetRotation(m_transformData.Rotation);
		trans->SetParent(GetThis<BombRemainingCount>());
		ApplyTransform();
	}

	void BombRemainingCount::OnUpdate() {
		m_number->SetValue(m_player->GetBombCount());
	}

	void BombRemainingCount::OnDraw() {
		m_number->OnDraw();
	}
}