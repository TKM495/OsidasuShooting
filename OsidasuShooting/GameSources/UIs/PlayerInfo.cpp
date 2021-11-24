#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerInfo::OnCreate() {
		auto armorGauge = ObjectFactory::Create<ArmorGauge>(GetStage(),
			m_owner, TransformData(Vec3(0.0f), Vec3(0.1f)));
		armorGauge->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(armorGauge);

		auto t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", 0, Vec3(0));
		t->GetTransform()->SetPosition(Vec3(-100.0f, -5.0f, 0.0f));
		t->GetTransform()->SetScale(Vec3(0.3f));
		t->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(t);

		int playerNumber = (int)m_owner->GetPlayerNumber();
		t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", playerNumber + 1, Vec3(0));
		t->GetTransform()->SetPosition(Vec3(-100.0f, -5.0f, 0.0f));
		t->GetTransform()->SetScale(Vec3(0.3f));
		t->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(t);

		ApplyTransform();
	}
	void PlayerInfo::OnUpdate() {
		for (auto uiObject : m_uiObjects) {
			uiObject->OnUpdate();
		}
	}
	void PlayerInfo::OnDraw() {
		for (auto uiObject : m_uiObjects) {
			uiObject->OnDraw();
		}
	}
}