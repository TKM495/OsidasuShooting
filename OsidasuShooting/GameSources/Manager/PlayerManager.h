/*!
@file   PlayerManager.h
@brief  プレイヤーを管理するクラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"

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
	class PlayerBase;

	class PlayerManager {
#pragma region  Singleton
	private:
		// カスタム削除子。インスタンスの削除はここからのみ行なう。
		struct Deleter {
			void operator()(PlayerManager const* const p) const {
				delete p;
			}
		};
		// std::unique_ptr は削除子を指定出来る
		static unique_ptr<PlayerManager, Deleter> m_instance;

		PlayerManager() {}
		~PlayerManager() {}
	public:
		/**
		 * @brief インスタンスの取得（必要があれば生成する）
		 *
		 * @return インスタンス
		 */
		static unique_ptr<PlayerManager, Deleter>& GetInstance() {
			if (!m_instance) {
				m_instance.reset(new PlayerManager);
			}
			return m_instance;
		}
		/**
		 * @brief インスタンスの強制削除
		 */
		static void DeleteInstance() {
			if (m_instance.get()) {
				m_instance.reset();
			}
		}
#pragma endregion

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
