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
		WORD LeftMotorSpeed;	// 左モーター（0～65535）

		/**
		 * @brief コンストラクタ
		 *
		 * @param rightMotorSpeedRate	// 右モーターの回転速度（0～1）(高回転)
		 * @param leftMotorSpeedRate	// 左モーターの回転速度（0～1）(低回転)
		 * @param time					// 継続時間
		 */
		VibrationData(float rightMotorSpeedRate, float leftMotorSpeedRate, float time) {
			this->RightMotorSpeed = WORD(65535 * Utility::Clamp(rightMotorSpeedRate, 0.0f, 1.0f));
			this->LeftMotorSpeed = WORD(65535 * Utility::Clamp(leftMotorSpeedRate, 0.0f, 1.0f));
			this->Time = time;
		}
		/**
		 * @brief コンストラクタ
		 *
		 * @param rightMotorSpeedRate	// 右モーターの回転速度（0～1）(高回転)
		 * @param leftMotorSpeedRate	// 左モーターの回転速度（0～1）(低回転)
		 */
		VibrationData(float rightMotorSpeedRate, float leftMotorSpeedRate) {
			this->RightMotorSpeed = WORD(65535 * Utility::Clamp(rightMotorSpeedRate, 0.0f, 1.0f));
			this->LeftMotorSpeed = WORD(65535 * Utility::Clamp(leftMotorSpeedRate, 0.0f, 1.0f));
			this->Time = INFINITY;
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

		// キーとバイブレーション動作フラグのマップ
		// 例：停止するAの処理と起動するBの処理があるとき
		// BのあとにAを実行するとBが想定通りの動作をしないのを防ぐ
		map<wstring, bool> m_vibrationMap;

		// プレイヤー番号（取得するコントローラーに影響）
		PlayerNumber m_playerNumber;

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

		/**
		 * @brief バイブレーションのアクティブ（スレッド用関数）
		 *
		 * @param key バイブレーションを識別するためのキー
		 * @param data バイブレーションデータ
		 */
		void ActiveVibrationThread(const wstring& key, const VibrationData& data);
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param number プレイヤー番号
		 */
		GameController(PlayerNumber number);
		/**
		 * @brief デストラクタ
		 */
		~GameController();

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

		/**
		 * @brief バイブレーションのセット
		 *
		 * @param key バイブレーションを識別するためのキー
		 * @param data バイブレーションデータ
		 */
		void SetVibration(const wstring& key, const VibrationData& data);

		/**
		 * @brief バイブレーションの停止
		 *
		 * @param key バイブレーションを識別するためのキー
		 */
		void StopVibration(const wstring& key);

		/**
		 * @brief バイブレーションのリセット
		 */
		void ResetVibration();
	};
}
