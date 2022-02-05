/*!
@file   ManualPlayer.cpp
@brief  �蓮����̃v���C���[�̎���
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ManualPlayer::OnCreate() {
		PlayerBase::OnCreate();
		m_knockBackCallback = [this](float strength) {
			KnockBackVibration(strength);
		};
		m_bumperCallback = [this] {
			m_controller.SetVibration(L"BumperHit",
				VibrationData(0.7f, 0, 0.1f));
		};
	}

	void ManualPlayer::KnockBackVibration(float strength) {
		float remapStrength = Utility::Remap(strength, 0, 1, 0, 0.7f);
		m_controller.SetVibration(L"Hit",
			VibrationData(remapStrength, remapStrength * 0.5f, 0.1f));
	}

	void ManualPlayer::InputUpdate() {
		// ���ڃX�e�B�b�N�����擾
		m_inputData.MoveDirection = m_controller.GetLeftStickVec();
		// ���e���[�h�ւ̐؂�ւ�
		m_inputData.IsSwitchBombMode = m_controller.GetLeftTrigger();

		// �W�����v�ƃz�o�[
		m_inputData.IsJumpOrHover = m_controller.GetButtons(ControllerButton::A);
		// �^�b�N��
		m_inputData.IsTackleMode = m_controller.GetButtons(ControllerButton::B);

		// ���[�h�ɉ�����Aim����
		if (m_inputData.IsSwitchBombMode) {
			m_inputData.BombAim = m_controller.GetRightStickVec();
		}
		else {
			m_inputData.BulletAim = m_controller.GetRightStickVec();
		}

		m_inputData.IsFire = m_controller.GetRightTrigger();

		// �z�o�[���Ȃ�
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

	// ---------------------------------------------------------------------
	// ---------------------------------------------------------------------

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