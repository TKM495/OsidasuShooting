/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkInterface.h"
#include "Utility/TimeCounter.h"
#include "JonyMd/CountDown.h"
#include "UIs/GameStartAndFinish.h"

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
		//���݂̃X�e�[�g
		GameState m_gameState;
		// �^�C�}�[�̕\���I�u�W�F�N�g
		shared_ptr<CountDown> m_countDown;
		// �X�^�[�g���̃J�E���g�_�E��
		shared_ptr<StartCountDown> m_startCountDown;
		// �ėp�I�ȃ^�C�}�[
		TimeCounter m_utilTimer;
		// �r���[�̍쐬
		void CreateViewLight();
	public:
		GameStage()
			: Stage(), m_gameState(GameState::FADEOUT), m_utilTimer(0.0f)
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
