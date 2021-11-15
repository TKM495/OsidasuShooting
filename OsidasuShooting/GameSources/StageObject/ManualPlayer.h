/*!
@file   ManualPlayer.h
@brief  �蓮����̃v���C���[
 */

#pragma once
#include "stdafx.h"
#include "Manager/ControllerManager.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	// ��ŏ���
	class ManualPlayer;
	using Player = ManualPlayer;

	class ManualPlayer :public PlayerBase {
		void InputUpdate()override;
		ControllerManager m_controllerManager;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W�ւ̃|�C���^
		 * @param transformData �g�����X�t�H�[���f�[�^
		 * @param playerNumber �v���C���[�̔ԍ�
		 */
		ManualPlayer(const shared_ptr<Stage>& stage,
			const TransformData& transformData,
			PlayerNumber playerNumber = PlayerNumber::P1)
			:PlayerBase(stage, transformData),
			m_controllerManager(playerNumber)
		{}
	};
}
