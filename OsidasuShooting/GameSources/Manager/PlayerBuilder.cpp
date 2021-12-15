#include "stdafx.h"
#include "Project.h"

namespace basecross {
	PlayerBuilder::PlayerBuilder(const shared_ptr<Stage>& stage, const wstring& line)
		:AdvancedGameObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_transformData.Position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_transformData.Scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_transformData.Rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
		// 1～4を0～3に変換
		m_playerNumber = (PlayerNumber)(_wtof(tokens[10].c_str()) - 1);
		m_operationType = OperationType::Manual;
	}

	void PlayerBuilder::OnCreate() {
		// いずれは外部ファイルに書く
		const map<PlayerNumber, Vec3> UIPosMap = {
			{PlayerNumber::P1,Vec3(-480.0f, -250.0f, 0.0f)},
			{PlayerNumber::P2,Vec3(-170.0f, -250.0f, 0.0f)},
			{PlayerNumber::P3,Vec3(170.0f, -250.0f, 0.0f)},
			{PlayerNumber::P4,Vec3(480.0f, -250.0f, 0.0f)},
		};
		// タイプごとに構築
		switch (m_operationType)
		{
		case OperationType::Manual:
		{
			auto playerType = StageManager::GetInstance()->GetPlayerType(m_playerNumber);
			auto player = InstantiateGameObject<ManualPlayer>(m_transformData, m_playerNumber, playerType);
			InstantiateGameObject<PlayerInfo>(player, TransformData(UIPosMap.at(m_playerNumber)));
			InstantiateGameObject<PlayerFollowUI>(player, TransformData());
			InstantiateGameObject<PlayerPositionUI>(player, TransformData());
			PlayerManager::GetInstance()->AddPlayer(player);
		}
		break;
		case OperationType::CPU:
			// 現在未実装
			//InstantiateGameObject<CPUPlayer>();
			break;
		default:
			break;
		}
		Destroy<PlayerBuilder>();
	}
}