/*!
@file   ManualPlayer.cpp
@brief  手動操作のプレイヤーの実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ManualPlayer::InputUpdate() {
		// 直接スティック情報を取得
		m_inputData.MoveDirection = m_controller.GetLeftStickVec();
		// 爆弾モードへの切り替え
		m_inputData.IsSwitchBombMode = m_controller.GetLeftTrigger();

		// ジャンプとホバー
		m_inputData.IsJumpOrHover = m_controller.GetButtons(ControllerButton::A);
		// タックル
		m_inputData.IsTackleMode = m_controller.GetButtons(ControllerButton::B);

		// モードに応じたAim操作
		if (m_inputData.IsSwitchBombMode) {
			m_inputData.BombAim = m_controller.GetRightStickVec();
		}
		else {
			m_inputData.BulletAim = m_controller.GetRightStickVec();
		}

		m_inputData.IsFire = m_controller.GetRightTrigger();

		// ホバー中なら
		if (IsHoverMode()) {
			m_controller.SetVibration(L"Hover", VibrationData(0.25f, 0.125f));
		}
	}

	void ManualPlayer::OnRespawn() {
		m_controller.SetVibration(L"Died", VibrationData(1.0f, 1.0f, 0.5f));
	}

	void ManualPlayer::OnStopHover() {
		m_controller.StopVibration(L"Hover");
	}

	void ResultPlayer::OnCreate() {
		PlayerBase::OnCreate();
	}
	void ResultPlayer::PlayWait() {
		m_model.lock()->StartWaitAnimation();
	}
	void ResultPlayer::PlayWin() {
		m_model.lock()->StartWinAnimation();
	}
}