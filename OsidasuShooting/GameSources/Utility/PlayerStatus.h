#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"
#include "StageObject/PlayerBase.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	/**
	 * @brief プレイヤー共通のステータス
	 */
	struct PlayerCommonStatus {
		float DefaultEnergy;        // デフォルトのエネルギー値
		float CorrectAngle;         // 弾の照準の補正角度
		float BombAimMovingDistance;// 爆弾の照準の移動量
		float BulletAimLineLength;  // 弾の照準線の長さ
		int DefaultBombCount;       // デフォルトの爆弾の所持数
		float GravityMagnification; // 重力
		float BombPowerDiameter;//爆弾の威力倍率
		float ShieldPerformanceIsDownEnergyRate; //シールドの性能が落ちるエネルギーの割合
	};
	/**
	 * @brief プレイヤー別のステータス
	 */
	struct StatusByPlayer {
		float MoveSpeed;            // 移動速度
		float JumpAmount;           // ジャンプ量
		float Power;				// 威力
		float BulletRateOfFire;     // 弾の発射速度
		float BombReloadSpeed;      // 爆弾のリロード速度
		float Weight;               // 重さ
		float EnergyUseInBulletShot;// 弾の発射に使用するエネルギー(1発あたり)
		float UseEnergyInHover;     // ホバーで消費するエネルギー(毎秒)
		float EnergyRecoveryAmount; // エネルギーの回復速度
		float BulletSize;			// 弾のサイズ
	};

	class PlayerStatus :public BaseSingleton<PlayerStatus> {
	private:
		PlayerStatus() :BaseSingleton() {
			DataExtraction();
		}
		~PlayerStatus() {}
		friend class BaseSingleton<PlayerStatus>;
	private:
		map<PlayerNumber, Col4> m_colorTable;
		PlayerCommonStatus m_commonStatus;
		map<PlayerType, StatusByPlayer> m_statusByPlayer;
	public:
		void DataExtraction();
		Col4 GetPlayerColor(PlayerNumber number);
		Col4 GetPlayerColor(int number);
		void SetPlayerData(const shared_ptr<PlayerBase>& player);
		shared_ptr<StatusByPlayer> GetStatusByPlayer(PlayerType type);
	};
}
