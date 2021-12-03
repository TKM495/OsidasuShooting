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
		int m_playersScore;
		PlayerNumber m_playerTop;
		int m_playerTopScore;
	public:
		ResultStage() :
			Stage(),
			str(),
			m_playersNumber(),
			m_playersScore(),
			m_playerTop(),
			m_playerTopScore()
		{}

		~ResultStage() {}

		shared_ptr<ResultScore> m_score;

		void OnCreate() override;
		void OnUpdate() override;

		void Players();

		void PlayersResult();
		void WinnerPlayer();

		void AddWinnwe();
		void AddWinnerSprite(int player);
		void AddResultDataSprite(Vec3 pos, int playerNum, int score);
		void BattlePlayerUISet(int value) {};
	};
}
