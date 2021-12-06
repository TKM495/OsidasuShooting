/*!
@file   ManualPlayer.cpp
@brief  手動操作のプレイヤーの実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ManualPlayer::InputUpdate() {
		// コントローラーを取得
		const auto& ctrlPad = m_controller.GetControler();
		// 直接スティック情報を取得
		m_inputData.MoveDirection = m_controller.GetLeftStickVec();
		// 爆弾モードへの切り替え
		m_inputData.IsSwitchBombMode = m_controller.GetRightTrigger();
		// 必殺技の発動
		m_inputData.IsInvokeSpecialSkill =
			ctrlPad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER &&
			ctrlPad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		// ジャンプとホバー
		m_inputData.IsJumpOrHover = m_controller.GetLeftTrigger();

		// モードに応じたAim操作
		if (m_inputData.IsSwitchBombMode) {
			m_inputData.BombAim = m_controller.GetRightStickVec();
		}
		else {
			m_inputData.BulletAim = m_controller.GetRightStickVec();
		}
	}

	void ResultPlayer::InputUpdate() {
		// コントローラーを取得
		const auto& ctrlPad = m_controller.GetControler();
		// ジャンプとホバー
		m_inputData.IsJumpOrHover = ctrlPad.bLeftTrigger > 128.0f;
	}
}