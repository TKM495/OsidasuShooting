#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerFollowUI::OnCreate() {
		auto data = CSVLoad::GetInstance()->GetData(L"PlayerFollowUI");
		auto tokens = Extracter::DelimitData(data[1]);
		auto transData = Extracter::TransformDataExtraction(tokens);

		auto armorGauge = ObjectFactory::Create<HoverTimeGauge>(GetStage(),
			m_owner, transData);
		armorGauge->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_uiObjects.push_back(armorGauge);

		tokens = Extracter::DelimitData(data[2]);
		transData = Extracter::TransformDataExtraction(tokens);

		auto bombReloadTimeGauge = ObjectFactory::Create<BombReloadTimeGauge>(GetStage(),
			m_owner, transData);
		bombReloadTimeGauge->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_uiObjects.push_back(bombReloadTimeGauge);

		tokens = Extracter::DelimitData(data[3]);
		transData = Extracter::TransformDataExtraction(tokens);

		auto bombCount = ObjectFactory::Create<BombRemainingCount>(GetStage(),
			m_owner, transData);
		bombCount->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_uiObjects.push_back(bombCount);

		tokens = Extracter::DelimitData(data[4]);
		transData = Extracter::TransformDataExtraction(tokens);

		int playerNumber = (int)m_owner->GetPlayerNumber();
		auto t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", playerNumber + 1, Vec3(0));
		t->GetTransform()->SetPosition(transData.Position);
		t->GetTransform()->SetScale(transData.Scale);
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