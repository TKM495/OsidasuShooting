/*!
@file   ManualPlayer.h
@brief  手動操作のプレイヤー
 */

#pragma once
#include "stdafx.h"
#include "Manager/ControllerManager.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	// 後で消す
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
			:PlayerBase(stage, transformData),
			m_controllerManager(playerNumber)
		{}
	};
}
