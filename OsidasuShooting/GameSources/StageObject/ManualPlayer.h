/*!
@file   ManualPlayer.h
@brief  手動操作のプレイヤー
 */

#pragma once
#include "stdafx.h"
#include "Manager/ControllerManager.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	// 後で消す（SpCameraで使用中）
	class ManualPlayer;
	using Player = ManualPlayer;

	class ManualPlayer :public PlayerBase {
		void InputUpdate()override;
		ControllerManager m_controllerManager;
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
			PlayerNumber playerNumber = PlayerNumber::P1)
			:PlayerBase(stage, transformData, playerNumber),
			m_controllerManager(playerNumber)
		{}
	};

	// リザルト用のプレイヤー
	class ResultPlayer :public PlayerBase {
		void InputUpdate()override;
		ControllerManager m_controllerManager;
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
			PlayerNumber playerNumber = PlayerNumber::P1)
			:PlayerBase(stage, transformData, playerNumber),
			m_controllerManager(playerNumber)
		{}
	};
}
