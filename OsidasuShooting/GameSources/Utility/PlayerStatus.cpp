#include "stdafx.h"
#include "Project.h"
#include "flatbuffers/util.h"

namespace basecross {
	// インスタンスの初期化
	unique_ptr<PlayerStatus, PlayerStatus::Deleter> PlayerStatus::m_instance = nullptr;

	void PlayerStatus::DataExtraction() {
		// XMLのデータを取得
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		// プレイヤーの色情報を取得
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/PlayerColor");
		// 4プレイヤー分の色を空白で4つのデータに分ける
		auto colorStrVec = DataExtracter::DelimitData(data, L' ');
		for (int i = 0; i < 4; i++) {
			// プレイヤー番号に応じた色データをRGBAに分類
			auto colorStr = DataExtracter::DelimitData(colorStrVec[i]);
			// 分類したものをCol4に変換
			auto color = DataExtracter::ColorDataExtraction(colorStr);
			// 0～1に変換
			m_colorTable[PlayerNumber(i)] = Utility::ConvertColorZeroToOne(color);
		}

		data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/CommonStatus");
		// 空白で区切って複数データに分ける
		auto statusStr = DataExtracter::DelimitData(data, L' ');
		// 文字列のデータを数値に変換
		vector<float> status;
		for (auto stat : statusStr) {
			status.push_back((float)_wtof(stat.c_str()));
		}
		PlayerCommonStatus common = {};
		common.DefaultEnergy = status[0];
		common.CorrectAngle = status[1];
		common.BombAimMovingDistance = status[2];
		common.BulletAimLineLength = status[3];
		common.DefaultBombCount = (int)status[4];
		common.GravityMagnification = status[5];
		common.BombPowerDiameter = status[6];
		common.ShieldPerformanceIsDownEnergyRate = status[7];

		m_commonStatus = common;

		for (int i = 0; i < 2; i++) {
			wstring type;
			switch (PlayerType(i)) {
			case PlayerType::Laser:
				type = L"LaserStatus";
				break;
			case PlayerType::Missile:
				type = L"MissileStatus";
				break;
			default:
				throw BaseException(
					L"定義されていないか未実装です。",
					L"switch (m_playerType)",
					L"PlayerBase::StatusLoad()");
				break;
			}
			auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/" + type);
			// 空白で区切って複数データに分ける
			statusStr = DataExtracter::DelimitData(data, L' ');
			// 文字列のデータを数値に変換
			status.clear();
			for (auto stat : statusStr) {
				status.push_back((float)_wtof(stat.c_str()));
			}

			StatusByPlayer byPlayer = {};
			byPlayer.MoveSpeed = status[0];
			byPlayer.JumpAmount = status[1];
			byPlayer.Power = status[2];
			byPlayer.BulletRateOfFire = status[3];
			byPlayer.BombReloadSpeed = status[4];
			byPlayer.Weight = status[5];
			byPlayer.EnergyUseInBulletShot = status[6];
			byPlayer.UseEnergyInHover = status[7];
			byPlayer.EnergyRecoveryAmount = status[8];
			byPlayer.BulletSize = status[9];
			m_statusByPlayer[PlayerType(i)] = byPlayer;
		}
	}

	Col4 PlayerStatus::GetPlayerColor(PlayerNumber number) {
		return m_colorTable[number];
	}
	Col4 PlayerStatus::GetPlayerColor(int number) {
		return GetPlayerColor(PlayerNumber(number - 1));
	}

	shared_ptr<StatusByPlayer> PlayerStatus::GetStatusByPlayer(PlayerType type) {
		return make_shared<StatusByPlayer>(m_statusByPlayer[type]);
	}

	void PlayerStatus::SetPlayerData(const shared_ptr<PlayerBase>& player) {
		player->m_defaultEnergy = m_commonStatus.DefaultEnergy;
		player->m_correctAngle = m_commonStatus.CorrectAngle;
		player->m_bombAimMovingDistance = m_commonStatus.BombAimMovingDistance;
		player->m_defaultBombCount = m_commonStatus.DefaultBombCount;
		player->m_bulletAimLineLength = m_commonStatus.BulletAimLineLength;
		auto defaultGravity = player->GetComponent<Gravity>()->GetGravity();
		player->GetComponent<Gravity>()->SetGravity(defaultGravity * m_commonStatus.GravityMagnification);
		player->m_shieldRate = m_commonStatus.ShieldPerformanceIsDownEnergyRate;
		const auto& data = m_statusByPlayer[player->GetPlayerType()];

		player->m_moveSpeed = data.MoveSpeed;
		player->m_jumpVerocity = Vec3(0, data.JumpAmount, 0);
		player->m_bulletPower = data.Power;
		player->m_bombPower = data.Power * m_commonStatus.BombPowerDiameter;
		player->m_bulletTimer.SetIntervalTime(data.BulletRateOfFire, true);
		player->m_bombCoolTimeTimer.SetIntervalTime(data.BombReloadSpeed, true);
		player->m_weight = data.Weight;
		player->m_energyRequiredInBulletLaunch = data.EnergyUseInBulletShot;
		player->m_energyRequiredInHover = data.UseEnergyInHover;
		player->m_energyRecoveryAmount = data.EnergyRecoveryAmount;
	}
}