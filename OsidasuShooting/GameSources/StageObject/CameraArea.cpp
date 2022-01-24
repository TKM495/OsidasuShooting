#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CameraArea::CameraArea(const shared_ptr<Stage>& stage, const wstring& line)
		: AdvancedGameObject(stage)
	{
		auto tokens = DataExtracter::DelimitData(line);
		m_area = Vec2(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str())
		);
	}

	void CameraArea::OnCreate() {
		auto cam = GetStage()->GetView()->GetTargetCamera();
		auto gameCam = dynamic_pointer_cast<GameCamera>(cam);
		if (gameCam) {
			gameCam->SetArea(m_area);
		}
		Destroy<CameraArea>();
	}
}