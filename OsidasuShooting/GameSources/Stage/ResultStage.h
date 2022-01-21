/*!
@file   ResultStage.h
@brief  ���U���g�X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "UIs/ResultScore.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class ResultStage :public Stage {
		// �r���[�̍쐬
		void CreateViewLight();

		wstring str;
		PlayerNumber m_playersNumber;
		int  m_playersScore;
		int  m_playersDead;
		Col4 m_playerColor[4];

		int  m_previousScore;
		int  m_previousDead;

		PlayerNumber m_playerTop;
		int  m_playerTopScore;
		int  m_playerTopDead;
		Col4 m_playerTopColor;

		PlayerNumber m_playerDraw[3];	// �g�b�v�Ɠ��_�̃v���C���[
		bool m_isPlayerDraw[3];			// �g�b�v�Ɠ��X�Ȃ�true

		int m_playersRank[4];			// �v���C���[

		bool m_isTopOnly; // �g�b�v�̃v���C���[����l���ǂ���

		bool m_sceneChangeBlock;
	public:
		ResultStage() :
			Stage(),
			str(),
			m_playersNumber(),
			m_playersScore(),
			m_playersDead(),
			m_playerColor(),
			m_previousScore(),
			m_previousDead(),
			m_playerTop(),
			m_playerTopScore(),
			m_playerTopDead(),
			m_playerTopColor(),
			m_playerDraw{},
			m_isPlayerDraw{false},
			m_isTopOnly(false),
			m_sceneChangeBlock(false)
		{}

		~ResultStage() {}

		shared_ptr<ResultScore> m_score;
		shared_ptr<ResultScore> m_dead;

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;

		void Players();

		void PlayersResult();
		void WinnerPlayer();

		void AddWinnwe();
		void AddWinnerSprite(int player);
		void AddResultSprites(Vec3 pos, int playerNum, int score, int dead,int rank);
		void RankingPlayerSet(Vec3 pos ,int value);
		void WinOrDraw(shared_ptr<PlayerBase> player, int loop, int drawPlayer);
		void BattlePlayerUISet(int value) {} ;
	};
}
