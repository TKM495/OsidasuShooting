/*!
@file   PlayerManager.h
@brief  プレイヤーを管理するクラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	/**
	 * @brief プレイヤーナンバー
	 */
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	// これがないとなぜかエラーが出る
	// 追記：ヘッダーが循環参照しているのでこれがないとエラーになるっぽい
	class PlayerBase;

	class PlayerManager :public BaseSingleton<PlayerManager> {
	private: // シングルトン関係
		PlayerManager() :BaseSingleton() {}
		~PlayerManager() {}
		friend class BaseSingleton<PlayerManager>;
	private:
		vector<shared_ptr<PlayerBase>> m_players;
	public:
		/**
		 * @brief プレイヤーの追加
		 *
		 * @param playerPtr プレイヤーのポインタ
		 */
		void AddPlayer(const shared_ptr<PlayerBase>& playerPtr);

		/**
		 * @brief プレイヤーの取得
		 *
		 * @param playerNumber 取得したいプレイヤーナンバー
		 * @return プレイヤーのポインタ
		 */
		shared_ptr<PlayerBase> GetPlayer(PlayerNumber playerNumber);

		/**
		 * @brief すべてのプレイヤーを取得
		 *
		 * @return プレイヤーのポインタのベクター配列
		 */
		vector<shared_ptr<PlayerBase>> GetAllPlayer()const {
			return m_players;
		}

		/**
		 * @brief ソートされたプレイヤーデータの配列を取得
		 *
		 * @return 倒した数でソートされたプレイヤーのポインタのベクター配列
		 */
		vector<shared_ptr<PlayerBase>> GetSortedAllPlayer()const;
	};
}
