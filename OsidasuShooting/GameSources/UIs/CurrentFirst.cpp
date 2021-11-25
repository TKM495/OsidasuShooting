#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CurrentFirst::OnCreate() {
		m_uiObj = ObjectFactory::Create<BattlePlayersUIs>(GetStage(), L"BPsUIs", 6, Vec3(0));
		m_uiObj->GetTransform()->SetScale(Vec3(0.3f));
	}

	void CurrentFirst::OnUpdate() {
		auto firstPlayer = PlayerManager::GetInstance()->GetSortedAllPlayer()[0];
		auto pos = Utility::ConvertWorldToScreen(
			GetStage()->GetView(), firstPlayer->GetTransform()->GetPosition());
		m_uiObj->GetTransform()->SetPosition(pos + Vec3(-40.0f, 110.0f, 0.0f));
	}
	void CurrentFirst::OnDraw() {
		m_uiObj->OnDraw();
	}
}