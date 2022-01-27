/*!
@file GameStage.h
@brief ゲームステージ
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
		// スタート時のカウントダウン
		shared_ptr<StartCountDown> m_startCountDown;
		// アイテム生成オブジェクト
		shared_ptr<modifiedClass::ItemCreation> m_itemCreation;
		bool m_bOnceItem;
		// 汎用的なタイマー
		TimeCounter m_utilTimer;
		// 時間倍率
		float m_timeScale;
		// ビューの作成
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

		shared_ptr<modifiedClass::ItemCreation> GetItemCreation() {
			return m_itemCreation;
		}

		float GetTimeScale() {
			return m_timeScale;
		}
	};
}
