#include "stdafx.h"
#include "Project.h"

#include <iostream>
#include <algorithm>

namespace basecross {
	void PlayerFollowUI::OnCreate() {
		auto data = CSVLoad::GetInstance()->GetData(L"PlayerFollowUI");
		auto tokens = DataExtracter::DelimitData(data[1]);
		auto transData = DataExtracter::TransformDataExtraction(tokens);

		tokens = DataExtracter::DelimitData(data[5]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto back = ObjectFactory::Create<SimpleSprite>(GetStage(), L"BombBack", transData);
		back->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_objectsData.push_back(ObjectData(UIType::Bomb, back));

		tokens = DataExtracter::DelimitData(data[2]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto bombReloadTimeGauge = ObjectFactory::Create<BombReloadTimeGauge>(GetStage(),
			m_owner, transData);
		bombReloadTimeGauge->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_objectsData.push_back(ObjectData(UIType::Bomb, bombReloadTimeGauge));

		tokens = DataExtracter::DelimitData(data[3]);
		transData = DataExtracter::TransformDataExtraction(tokens);

		auto bombCount = ObjectFactory::Create<BombRemainingCount>(GetStage(),
			m_owner, transData);
		bombCount->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_objectsData.push_back(ObjectData(UIType::Bomb, bombCount));

		auto rank = ObjectFactory::Create<CurrentRank>(GetStage(),
			m_owner, TransformData());
		rank->GetTransform()->SetParent(GetThis<PlayerFollowUI>());
		m_objectsData.push_back(ObjectData(UIType::Rank, rank));

		ApplyTransform();
	}
	void PlayerFollowUI::OnUpdate() {
		auto pos = Utility::ConvertWorldToScreen(GetStage()->GetView(), m_owner->GetTransform()->GetPosition());

		GetTransform()->SetPosition(pos + m_offset);

		for (auto uiObject : m_objectsData) {
			uiObject.UIObject->OnUpdate();
		}
	}
	void PlayerFollowUI::OnDraw() {
		// プレイヤーが非アクティブの場合描画しない
		if (!m_owner->GetActive())
			return;

		for (auto uiObject : m_objectsData) {
			switch (uiObject.Type)
			{
			case UIType::Normal:
				uiObject.UIObject->OnDraw();
				break;
			case UIType::Bomb:
				if (m_owner->IsBombMode())
					uiObject.UIObject->OnDraw();
				break;
			case UIType::Rank:
			{
				auto gameStage = GetTypeStage<GameStage>(false);
				if (gameStage)
					if (gameStage->IsTurnOff30Sec())
						break;
				uiObject.UIObject->OnDraw();
			}
			break;
			default:
				break;
			}
		}
	}

	void PlayerPositionUI::OnCreate() {
		auto data = CSVLoad::GetInstance()->GetData(L"PlayerFollowUI");
		auto tokens = DataExtracter::DelimitData(data[4]);
		auto transData = DataExtracter::TransformDataExtraction(tokens);

		int playerNumber = (int)m_owner->GetPlayerNumber();
		auto t = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", playerNumber + 1, Vec3(0));
		t->GetTransform()->SetPosition(transData.Position);
		t->GetTransform()->SetScale(transData.Scale);
		t->GetTransform()->SetParent(GetThis<PlayerPositionUI>());
		t->GetDynamicComponent<SpriteBaseDraw>()->SetDiffuse(m_owner->GetColor());
		m_uiObject.push_back(t);

		//auto arrow = ObjectFactory::Create<SimpleSprite>(GetStage(), L"Arrow", TransformData());
		//m_uiObject.push_back(arrow);
	}

	void PlayerPositionUI::OnUpdate() {
		auto pos = Utility::ConvertWorldToScreen(GetStage()->GetView(), m_owner->GetTransform()->GetPosition());
		pos = ClampInScreen(pos);
		GetTransform()->SetPosition(pos + m_offset);

		for (auto uiObject : m_uiObject) {
			uiObject->OnUpdate();
		}
	}

	void PlayerPositionUI::OnDraw() {
		// プレイヤーが非アクティブの場合描画しない
		if (!m_owner->GetActive())
			return;

		for (auto uiObject : m_uiObject) {
			uiObject->OnDraw();
		}
	}

	Vec3 PlayerPositionUI::ClampInScreen(const Vec3& value) {
		auto viewport = GetStage()->GetView()->GetTargetViewport();
		auto screenSize = Vec3(viewport.Width * 0.95f, viewport.Height * 0.95f, 0);
		auto halfScreenSize = screenSize / 2.0f;
		auto clamped = Utility::ClampVector3(value, -halfScreenSize, halfScreenSize);
		return clamped;
	}
}