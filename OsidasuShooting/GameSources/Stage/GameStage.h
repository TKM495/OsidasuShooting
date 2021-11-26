/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkInterface.h"
#include "Utility/TimeCounter.h"
#include "JonyMd/CountDown.h"

namespace basecross {
	class GameStage : public Stage {
	public:
		// �Q�[���X�e�[�g
		enum class GameState {
			FADEOUT,		//�t�F�[�h�A�E�g�ҋ@
			STAY,		//�X�^�[�g�O
			PLAYING,	//�v���C��
			//PAUSE,		//�|�[�Y��
			CLEAR,		//�N���A��
			FADEIN		//�t�F�[�h�C���ҋ@
		};
	private:
		// �X�^�[�g���̃J�E���g�_�E���^�C�}�[
		TimeCounter m_startCountDownTimer;
		//���݂̃X�e�[�g
		GameState m_gameState;
		// �J�E���g�_�E���̕\���I�u�W�F�N�g
		weak_ptr<CountDown> m_countDown;
		// �r���[�̍쐬
		void CreateViewLight();
	public:
		GameStage()
			: Stage(), m_startCountDownTimer(3.0f),
			m_gameState(GameState::FADEOUT)
		{}
		~GameStage() {}

		void OnCreate()override;
		void OnUpdate()override;

		/**
		 * @brief �X�e�[�g�̕ύX
		 *
		 * @param state �ύX��̃X�e�[�g
		 */
		void ChangeGameState(GameState state);
		/**
		 * @brief ���݂̃X�e�[�g���擾
		 *
		 * @return ���݂̃X�e�[�g
		 */
		GameState GetCurrentGameState();
	};
}
