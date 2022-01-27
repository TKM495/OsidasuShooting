/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkInterface.h"
#include "Utility/TimeCounter.h"
#include "StageObject/ItemCreation_.h"
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
		// �X�^�[�g���̃J�E���g�_�E��
		shared_ptr<StartCountDown> m_startCountDown;
		// �A�C�e�������I�u�W�F�N�g
		shared_ptr<modifiedClass::ItemCreation> m_itemCreation;
		bool m_bOnceItem;
		// �ėp�I�ȃ^�C�}�[
		TimeCounter m_utilTimer;
		// ���Ԕ{��
		float m_timeScale;
		// �r���[�̍쐬
		void CreateViewLight();
		void ItemGeneration();
	public:
		GameStage()
			: Stage(), m_gameState(GameState::FADEOUT), m_utilTimer(0.0f),
			m_bOnceItem(false), m_timeScale(1.0f)
		{}
		~GameStage() {}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

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

		shared_ptr<modifiedClass::ItemCreation> GetItemCreation() {
			return m_itemCreation;
		}

		float GetTimeScale() {
			return m_timeScale;
		}
	};
}
