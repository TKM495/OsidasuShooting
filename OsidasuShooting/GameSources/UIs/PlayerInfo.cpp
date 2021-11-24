#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerInfo::OnCreate() {
		auto data = CSVLoad::GetInstance()->GetData(L"PlayerInfo");
		auto tokens = Extracter::DelimitData(data[1]);
		auto transData = Extracter::TransformDataExtraction(tokens);

		auto armorGauge = ObjectFactory::Create<ArmorGauge>(GetStage(),
			m_owner, transData);
		armorGauge->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(armorGauge);

		tokens = Extracter::DelimitData(data[2]);
		transData = Extracter::TransformDataExtraction(tokens);

		auto t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", 0, Vec3(0));
		t->GetTransform()->SetPosition(transData.Position);
		t->GetTransform()->SetScale(transData.Scale);
		t->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(t);

		tokens = Extracter::DelimitData(data[3]);
		transData = Extracter::TransformDataExtraction(tokens);

		int playerNumber = (int)m_owner->GetPlayerNumber();
		t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", playerNumber + 1, Vec3(0));
		t->GetTransform()->SetPosition(transData.Position);
		t->GetTransform()->SetScale(transData.Scale);
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