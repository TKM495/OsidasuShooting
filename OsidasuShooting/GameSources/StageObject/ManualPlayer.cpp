/*!
@file   ManualPlayer.cpp
@brief  �蓮����̃v���C���[�̎���
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ManualPlayer::InputUpdate() {
		// �R���g���[���[���擾
		const auto& ctrlPad = m_controller.GetControler();
		// ���ڃX�e�B�b�N�����擾
		m_inputData.MoveDirection = m_controller.GetLeftStickVec();
		// ���e���[�h�ւ̐؂�ւ�
		m_inputData.IsSwitchBombMode = m_controller.GetRightTrigger();
		// �K�E�Z�̔���
		m_inputData.IsInvokeSpecialSkill =
			ctrlPad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER &&
			ctrlPad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		// �W�����v�ƃz�o�[
		m_inputData.IsJumpOrHover = m_controller.GetLeftTrigger();

		// ���[�h�ɉ�����Aim����
		if (m_inputData.IsSwitchBombMode) {
			m_inputData.BombAim = m_controller.GetRightStickVec();
		}
		else {
			m_inputData.BulletAim = m_controller.GetRightStickVec();
		}
	}

	void ResultPlayer::InputUpdate() {
		// �R���g���[���[���擾
		const auto& ctrlPad = m_controller.GetControler();
		// �W�����v�ƃz�o�[
		m_inputData.IsJumpOrHover = ctrlPad.bLeftTrigger > 128.0f;
	}
}