/*!
@file   ResultStage.h
@brief  リザルトステージ
*/

#pragma once
#include "stdafx.h"
#include "UIs/ResultScore.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class ResultStage :public Stage {
		// ビューの作成
		void CreateViewLight();

		wstring str;
		PlayerNumber m_playersNumber;
		int  m_playersScore;
		int  m_playersDead;
		Col4 m_playerColor;

		PlayerNumber m_playerTop;
		int  m_playerTopScore;
		Col4 m_playerTopColor;

		bool m_isTopOnly; // トップのプレイヤーが一人かどうか

		bool m_sceneChangeBlock;
	public:
		ResultStage() :
			Stage(),
			str(),
			m_playersNumber(),
			m_playersScore(),
			m_playersDead(),
			m_playerColor(),
			m_playerTop(),
			m_playerTopScore(),
			m_playerTopColor(),
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
		void AddResultSprites(Vec3 pos, int playerNum, int score, int dead);
		void BattlePlayerUISet(int value) {} ;
	};
}
