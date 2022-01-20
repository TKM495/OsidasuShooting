#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleCamera::OnCreate() {
		AddComponent<PNTStaticDraw>()->SetMeshResource(L"DEFAULT_CUBE");

		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CSVLoad::GetInstance()->RegisterFile(L"Camera", DataDir + L"CSV/" + L"Camera.csv");
		auto line = CSVLoad::GetInstance()->GetData(L"Camera");
		auto data = DataExtracter::DelimitData(line[2]);
		auto eye = Vec3(
			(float)_wtof(data[1].c_str()),
			(float)_wtof(data[2].c_str()),
			(float)_wtof(data[3].c_str())
		);
		auto at = Vec3(
			(float)_wtof(data[4].c_str()),
			(float)_wtof(data[5].c_str()),
			(float)_wtof(data[6].c_str())
		);
		GetTransform()->SetPosition(eye);
		GetTransform()->SetRotation(at);
	}
	void TitleCamera::OnUpdate() {
	}
}