/*!
@file   StageManager.h
@brief  ステージマネージャー
*/

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	/**
	 * @brief プレイヤーのタイプ
	 */
	enum class PlayerType {
		Laser,
		Missile,
		ThreeWay
	};
	/**
	 * @brief セレクトステージでのデータを格納し、ゲームステージへデータを渡すためのクラス
	 */
	class StageManager :public BaseSingleton<StageManager> {
	private: //シングルトン関係
		StageManager() {}
		~StageManager() {}
		friend class BaseSingleton<StageManager>;
	private:
		// プレイヤー番号に応じたプレイヤーのタイプを格納するmap
		map<PlayerNumber, PlayerType> m_playerTypeMap;
		// ステージの番号
		int m_stageNumber;
	public:
		/**
		 * @brief プレイヤーのタイプをセット
		 *
		 * @param number プレイヤーの番号
		 * @param type プレイヤーのタイプ
		 */
		void SetPlayerType(PlayerNumber number, PlayerType type);
		/**
		 * @brief プレイヤーのタイプをセット
		 *
		 * @param number プレイヤーの番号（int 1～4）
		 * @param type プレイヤーのタイプ
		 */
		void SetPlayerType(int number, PlayerType type);
		/**
		 * @brief プレイヤーのタイプを取得
		 *
		 * @param number プレイバーの番号
		 * @return プレイヤーのタイプ
		 */
		PlayerType GetPlayerType(PlayerNumber number);
		/**
		 * @brief ステージ番号のセット
		 *
		 * @param number ステージ番号
		 */
		void SetStageNumber(int number);
		/**
		 * @brief ステージ番号の取得
		 *
		 * @return ステージ番号
		 */
		int GetStageNumber();
		/**
		 * @brief データのリセット
		 */
		void ResetData();
	};
}
