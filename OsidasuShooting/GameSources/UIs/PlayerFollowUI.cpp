#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerFollowUI::OnCreate() {
		auto armorGauge = ObjectFactory::Create<HoverTimeGauge>(GetStage(),
			m_owner, TransformData(Vec3(0.0f), Vec3(0.05f)));
		armorGauge->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_uiObjects.push_back(armorGauge);

		int playerNumber = (int)m_owner->GetPlayerNumber();
		auto t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", playerNumber + 1, Vec3(0));
		t->GetTransform()->SetPosition(Vec3(-100.0f, -5.0f, 0.0f));
		t->GetTransform()->SetScale(Vec3(0.2f));
		t->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_uiObjects.push_back(t);

		ApplyTransform();
	}
	void PlayerFollowUI::OnUpdate() {
		auto pos = Utility::ConvertWorldToScreen(GetStage()->GetView(), m_owner->GetTransform()->GetPosition());

		GetTransform()->SetPosition(pos + m_offset);

		for (auto uiObject : m_uiObjects) {
			uiObject->OnUpdate();
		}
	}
	void PlayerFollowUI::OnDraw() {
		for (auto uiObject : m_uiObjects) {
			uiObject->OnDraw();
		}
	}
}