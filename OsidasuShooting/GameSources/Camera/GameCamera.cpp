/*!
@file GameCamera.cpp
@brief ゲームカメラの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameCamera::GameCamera()
		:Camera(), m_state(State::Init), m_followUpVelocity(2.0f)
	{}

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
		switch (m_state)
		{
		case State::Init:
			Init();
			m_state = State::Update;
			break;
		case State::Update:
			Update();
			break;
		default:
			throw BaseException(
				L"未定義の値です。",
				L"switch (m_state)",
				L"void GameCamera::OnUpdate()"
			);
			break;
		}
	}

	void GameCamera::Init() {
		auto players = PlayerManager::GetInstance()->GetAllPlayer();
		Vec3 sumVec(0);
		for (const auto& player : players) {
			sumVec += player->GetTransform()->GetPosition();
		}
		auto averageAt = sumVec / (float)players.size();
		SetAt(m_defaultAt + averageAt);
		SetEye(GetAt() + m_defaultLocalEye);
	}

	void GameCamera::Update() {
		auto players = PlayerManager::GetInstance()->GetAllPlayer();

		// 各プレイヤーの中心をとって注視点・カメラ座標を移動させる処理
		Vec3 sumVec(0);
		for (const auto& player : players) {
			sumVec += player->GetTransform()->GetPosition();
		}
		auto averageAt = sumVec / (float)players.size();
		SetAtAndEye(m_defaultAt + averageAt);
	}

	void GameCamera::SetAtAndEye(const Vec3& at) {
		auto delta = App::GetApp()->GetElapsedTime();
		// 遅れて追従させる
		auto _at = Lerp::CalculateLerp(
			GetAt(), at,
			0, 1,
			m_followUpVelocity * delta,
			Lerp::rate::Linear
		);
		// AtとEyeをセット
		SetAt(_at);
		SetEye(GetAt() + m_defaultLocalEye);
	}
}