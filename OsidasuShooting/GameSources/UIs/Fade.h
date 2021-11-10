/*!
@file   Fade.h
@brief  フェードイン、アウト
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade :public GameObject {
		// フェードの状態(列挙型)
		enum class FadeState {
			Active,	// 動作中
			Stop	// 停止中
		};
		// フェードの状態
		FadeState m_state;
		// フェードの方向(フェードインなら-1,アウトなら1)
		int m_key;
		// フェードにかかる時間
		float m_fadeTime;
		// 時間計測用
		float m_delta;
		// フェードに使用する色
		Col4 m_color;
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージ
		 */
		Fade(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_state(FadeState::Stop),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_key(0),
			m_color(Col4(0.0f, 0.0f, 0.0f, 1.0f))
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		/**
		 * @brief フェードイン開始
		 */
		void FadeIn();
		/**
		 * @brief フェードアウト開始
		 */
		void FadeOut();

		/**
		 * @brief フェードまでの時間設定
		 *
		 * @param time 時間
		 */
		void SetFadeTime(float time) {
			m_fadeTime = time;
		}
		/**
		 * @brief フェードまでの時間取得
		 *
		 * @return フェードまでの時間
		 */
		float GetFadeTime() {
			return m_fadeTime;
		}
		/**
		 * @brief フェード時の色の設定
		 *
		 * @param color 色
		 */
		void SetFadeColor(Col4 color) {
			m_color = color;
		}
		/**
		 * @brief フェード時の色の取得
		 *
		 * @return フェード時の色
		 */
		Col4 GetFadeColor() {
			return m_color;
		}

		/**
		 * @brief 動作フラグ
		 *
		 * @return 動作していればtrue/停止しているときはfalse
		 */
		bool GetFadeActive() {
			return m_state == FadeState::Active;
		}
	};

}
//end basecross
