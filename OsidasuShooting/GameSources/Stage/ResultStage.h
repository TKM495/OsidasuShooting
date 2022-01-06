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
		int m_playersDead;
		PlayerNumber m_playerTop;
		int m_playerTopScore;

		bool m_sceneChangeBlock;
	public:
		ResultStage() :
			Stage(),
			str(),
			m_playersNumber(),
			m_playersScore(),
			m_playersDead(),
			m_playerTop(),
			m_playerTopScore(),
			m_sceneChangeBlock(false)
		{}

		~ResultStage() {}

		shared_ptr<ResultScore> m_score;

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
