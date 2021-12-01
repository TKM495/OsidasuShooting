/*!
@file GameStage.h
@brief ゲームステージ
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
		// ゲームステート
		enum class GameState {
			FADEOUT,		//フェードアウト待機
			STAY,		//スタート前
			PLAYING,	//プレイ時
			//PAUSE,		//ポーズ時
			CLEAR,		//クリア時
			FADEIN		//フェードイン待機
		};
	private:
		//現在のステート
		GameState m_gameState;
		// タイマーの表示オブジェクト
		shared_ptr<CountDown> m_countDown;
		// スタート時のカウントダウン
		shared_ptr<StartCountDown> m_startCountDown;
		// 汎用的なタイマー
		TimeCounter m_utilTimer;
		// ビューの作成
		void CreateViewLight();
	public:
		GameStage()
			: Stage(), m_gameState(GameState::FADEOUT), m_utilTimer(0.0f)
		{}
		~GameStage() {}

		void OnCreate()override;
		void OnUpdate()override;

		/**
		 * @brief ステートの変更
		 *
		 * @param state 変更先のステート
		 */
		void ChangeGameState(GameState state);
		/**
		 * @brief 現在のステートを取得
		 *
		 * @return 現在のステート
		 */
		GameState GetCurrentGameState();
	};
}
