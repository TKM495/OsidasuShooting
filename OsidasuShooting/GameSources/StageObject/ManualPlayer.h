/*!
@file   ManualPlayer.h
@brief  �蓮����̃v���C���[
 */

#pragma once
#include "stdafx.h"
#include "Utility/GameController.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	// ��ŏ����iSpCamera�Ŏg�p���j
	class ManualPlayer;
	using Player = ManualPlayer;

	class ManualPlayer :public PlayerBase {
		void InputUpdate()override;
		GameController m_controller;
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
			:PlayerBase(stage, transformData, playerNumber),
			m_controller(playerNumber)
		{}
	};

	// ���U���g�p�̃v���C���[
	class ResultPlayer :public PlayerBase {
		void InputUpdate()override;
		GameController m_controller;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W�ւ̃|�C���^
		 * @param transformData �g�����X�t�H�[���f�[�^
		 * @param playerNumber �v���C���[�̔ԍ�
		 */
		ResultPlayer(const shared_ptr<Stage>& stage,
			const TransformData& transformData,
			PlayerNumber playerNumber = PlayerNumber::P1)
			:PlayerBase(stage, transformData, playerNumber),
			m_controller(playerNumber)
		{}
	};
}
