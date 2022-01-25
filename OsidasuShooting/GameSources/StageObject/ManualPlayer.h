/*!
@file   ManualPlayer.h
@brief  手動操作のプレイヤー
 */

#pragma once
#include "stdafx.h"
#include "Utility/GameController.h"
#include "StageObject/PlayerBase.h"
#include "Manager/StageManager.h"

namespace basecross {
	// 後で消す（SpCameraで使用中）
	class ManualPlayer;
	using Player = ManualPlayer;

	class ManualPlayer :public PlayerBase {
		GameController m_controller;
		void InputUpdate()override;
		void OnRespawn()override;
		void OnStopHover()override;
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージへのポインタ
		 * @param transformData トランスフォームデータ
		 * @param playerNumber プレイヤーの番号
		 */
		ManualPlayer(const shared_ptr<Stage>& stage,
			const TransformData& transformData,
			PlayerNumber playerNumber = PlayerNumber::P1,
			PlayerType playerType = PlayerType::Laser)
			:PlayerBase(stage, transformData, playerNumber, playerType),
			m_controller(playerNumber)
		{}
	};

	// リザルト用のプレイヤー
	class ResultPlayer :public PlayerBase {
		void InputUpdate() {};
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージへのポインタ
		 * @param transformData トランスフォームデータ
		 * @param playerNumber プレイヤーの番号
		 */
		ResultPlayer(const shared_ptr<Stage>& stage,
			const TransformData& transformData,
			PlayerNumber playerNumber = PlayerNumber::P1,
			PlayerType playerType = PlayerType::Laser)
			:PlayerBase(stage, transformData, playerNumber, playerType)
		{}
		void OnCreate()override;
	};

	// タイトル用のプレイヤー
	class TitlePlayer : public PlayerBase {
		void InputUpdate() {};
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージへのポインタ
		 * @param transformData トランスフォームデータ
		 * @param playerNumber プレイヤーの番号
		 */
		TitlePlayer(const shared_ptr<Stage>& stage,
			const TransformData& transformData,
			PlayerNumber playerNumber = PlayerNumber::P1,
			PlayerType playerType = PlayerType::Laser)
			:PlayerBase(stage, transformData, playerNumber, playerType)
		{}
		//void OnCreate()override;
	};
}
