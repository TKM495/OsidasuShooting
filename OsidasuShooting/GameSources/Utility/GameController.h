/*!
@file   GameController.h
@brief  コントローラー管理クラス
 */

#pragma once
#include "stdafx.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	/**
	 * @brief バイブレーションデータ
	 */
	struct VibrationData
	{
		float Time;				// 継続時間
		WORD RightMotorSpeed;	// 右モーター（0～65535）
		WORD LeftMotorSpeed;		// 左モーター（0～65535）

		/**
		 * @brief コンストラクタ
		 *
		 * @param time				継続時間
		 * @param rightMotorSpeed	右モーター（0～65535）
		 * @param leftMotorSpeed	左モーター（0～65535）
		 */
		VibrationData(float time, WORD rightMotorSpeed, WORD leftMotorSpeed) {
			this->Time = time;
			this->RightMotorSpeed = rightMotorSpeed;
			this->LeftMotorSpeed = leftMotorSpeed;
		}
	};

	class GameController {
		/**
		 * @brief スティックの種類
		 */
		enum class Direction {
			Left,
			Right
		};

		// プレイヤー番号（取得するコントローラーに影響）
		PlayerNumber m_playerNumber;
		TimeCounter m_timer;
		/**
		 * @brief スティックを取得
		 *
		 * @param direction 取得したいスティック
		 * @return スティックのデータ（Vec2）
		 */
		Vec2 GetStickVec(Direction direction);
		/**
		 * @brief トリガーを取得
		 *
		 * @param direction 取得したいトリガー
		 * @return トリガーのデータ（bool）
		 */
		bool GetTrigger(Direction direction);
		void th(const VibrationData& data);
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param number プレイヤー番号
		 */
		GameController(PlayerNumber number);

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

		/**
		 * @brief 右トリガーが押されているか
		 *
		 * @return trueなら押されている
		 */
		bool GetRightTrigger();
		/**
		 * @brief 左トリガーが押されているか
		 *
		 * @return trueなら押されている
		 */
		bool GetLeftTrigger();

		void SetVibration(const VibrationData& data);
		void ResetVibration();
	};
}
