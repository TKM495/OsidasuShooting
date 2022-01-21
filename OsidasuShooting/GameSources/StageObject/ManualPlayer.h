/*!
@file   ManualPlayer.h
@brief  �蓮����̃v���C���[
 */

#pragma once
#include "stdafx.h"
#include "Utility/GameController.h"
#include "StageObject/PlayerBase.h"
#include "Manager/StageManager.h"

namespace basecross {
	// ��ŏ����iSpCamera�Ŏg�p���j
	class ManualPlayer;
	using Player = ManualPlayer;

	class ManualPlayer :public PlayerBase {
		GameController m_controller;
		void InputUpdate()override;
		void OnRespawn()override;
		void OnStopHover()override;
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
			PlayerNumber playerNumber = PlayerNumber::P1,
			PlayerType playerType = PlayerType::Laser)
			:PlayerBase(stage, transformData, playerNumber, playerType),
			m_controller(playerNumber)
		{}
	};

	// ���U���g�p�̃v���C���[
	class ResultPlayer :public PlayerBase {
		void InputUpdate() {};
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
			PlayerNumber playerNumber = PlayerNumber::P1,
			PlayerType playerType = PlayerType::Laser)
			:PlayerBase(stage, transformData, playerNumber, playerType)
		{}
		void OnCreate()override;
	};

	// �^�C�g���p�̃v���C���[
	class TitlePlayer : public PlayerBase {
		void InputUpdate() {};
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W�ւ̃|�C���^
		 * @param transformData �g�����X�t�H�[���f�[�^
		 * @param playerNumber �v���C���[�̔ԍ�
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
