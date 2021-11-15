/*!
@file   ControllerManager.h
@brief  コントローラーマネージャー
 */

#pragma once
#include "stdafx.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	class ControllerManager {
		/**
		 * @brief スティックの種類
		 */
		enum class Stick {
			Left,
			Right
		};

		// プレイヤー番号（取得するコントローラーに影響）
		PlayerNumber m_playerNumber;
		/**
		 * @brief スティックを取得
		 *
		 * @param stick 取得したいスティック
		 * @return スティックのデータ（Vec2）
		 */
		Vec2 GetStickVec(Stick stick);
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param number プレイヤー番号
		 */
		ControllerManager(PlayerNumber number);

		/**
		 * @brief コントローラー取得
		 *
		 * @return CONTROLER_STATE
		 */
		CONTROLER_STATE GetControler();

		/**
		 * @brief 左スティックの取得
		 *
		 * @return Vec3のベクトル
		 */
		Vec3 GetLeftStickVec();

		/**
		 * @brief 右スティックの取得
		 *
		 * @return Vec3のベクトル
		 */
		Vec3 GetRightStickVec();
	};
}
