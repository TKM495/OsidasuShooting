#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerInfo::OnCreate() {
		auto data = CSVLoad::GetInstance()->GetData(L"PlayerInfo");
		auto tokens = DataExtracter::DelimitData(data[4]);
		auto transData = DataExtracter::TransformDataExtraction(tokens);

		auto back = ObjectFactory::Create<SimpleSprite>(GetStage(), L"GaugeBackGround", transData);
		back->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(back);

		tokens = DataExtracter::DelimitData(data[1]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto energyGauge = ObjectFactory::Create<EnergyGauge>(GetStage(),
			m_owner, transData);
		energyGauge->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(energyGauge);

		tokens = DataExtracter::DelimitData(data[2]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto playerType = (int)m_owner->GetPlayerType();
		auto t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs2", playerType, Vec3(0));
		t->GetTransform()->SetPosition(transData.Position);
		t->GetTransform()->SetScale(transData.Scale);
		t->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(t);

		tokens = DataExtracter::DelimitData(data[3]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		int playerNumber = (int)m_owner->GetPlayerNumber();
		t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", playerNumber + 1, Vec3(0));
		t->GetTransform()->SetPosition(transData.Position);
		t->GetTransform()->SetScale(transData.Scale);
		t->GetTransform()->SetParent(GetThis<PlayerInfo>());
		t->GetDynamicComponent<SpriteBaseDraw>()->SetDiffuse(m_owner->GetColor());
		m_uiObjects.push_back(t);

		tokens = DataExtracter::DelimitData(data[5]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto bombBack = ObjectFactory::Create<SimpleSprite>(GetStage(), L"BomberUI", transData);
		bombBack->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(bombBack);

		tokens = DataExtracter::DelimitData(data[6]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto bombCount = ObjectFactory::Create<BombRemainingCount>(GetStage(),
			m_owner, transData);
		bombCount->GetTransform()->SetParent(GetThis<PlayerInfo>());
		m_uiObjects.push_back(bombCount);

		ApplyTransform();

		m_lastKillCount = m_owner->GetCountKilledPlayer();
	}
	void PlayerInfo::OnUpdate() {
		for (auto uiObject : m_uiObjects) {
			uiObject->OnUpdate();
		}
		if (m_owner->GetCountKilledPlayer() != m_lastKillCount) {
			int count = m_owner->GetCountKilledPlayer() - m_lastKillCount;
			auto transData = TransformData(
				m_transformData.Position + Vec3(40, 10, 0),
				Vec3(0.2f)
			);

			for (int i = 0; i < count; i++) {
				auto obj = InstantiateGameObject<OneShotUI>(
					nullptr,
					1.0f, L"Kill", transData
					);
				obj->SetColor(m_owner->GetColor());
			}
		}
		m_lastKillCount = m_owner->GetCountKilledPlayer();
	}
	void PlayerInfo::OnDraw() {
		for (auto uiObject : m_uiObjects) {
			uiObject->OnDraw();
		}
	}
}