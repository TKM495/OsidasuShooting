#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameCamera::OnCreate() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CSVLoad::GetInstance()->RegisterFile(L"Camera", DataDir + L"CSV/" + L"Camera.csv");
		auto line = CSVLoad::GetInstance()->GetData(L"Camera");
		auto data = DataExtracter::DelimitData(line[1]);
		auto eye = Vec3(
			(float)_wtof(data[1].c_str()),
			(float)_wtof(data[2].c_str()),
			(float)_wtof(data[3].c_str())
		);
		m_defaultAt = Vec3(
			(float)_wtof(data[4].c_str()),
			(float)_wtof(data[5].c_str()),
			(float)_wtof(data[6].c_str())
		);
		m_defaultLocalEye = eye - m_defaultAt;
		SetEye(m_defaultAt + m_defaultLocalEye);
		SetAt(m_defaultAt);
	}

	void GameCamera::OnUpdate() {
		auto players = PlayerManager::GetInstance()->GetAllPlayer();
		// ƒvƒŒƒCƒ„[‚ÌŠi”[‚ª
		if (players.empty()) {
			SetEye(m_defaultAt + m_defaultLocalEye);
			SetAt(m_defaultAt);
			return;
		}
	}
}