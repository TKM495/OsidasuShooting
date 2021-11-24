/*!
@file   FadeComponent.h
@brief  フェードコンポーネント
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	class FadeComponent :public Component {
		// フェードの方向
		enum class Direction {
			FadeIn,
			FadeOut
		};
		// フェードの方向
		Direction m_dir;
		// フェードが動作中かどうか
		bool m_bActive;
		// フェードにかかる時間
		float m_fadeTime;
		// 時間計測用
		float m_delta;
		// 色
		Col4 m_color;
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param objPtr オブジェクトポインタ
		 */
		FadeComponent(const shared_ptr<GameObject>& objPtr)
			:Component(objPtr),
			m_dir(Direction::FadeIn),
			m_bActive(false),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_color(Col4(0.0f))
		{}
		virtual void OnUpdate()override;
		virtual void OnDraw()override{}

		/**
		 * @brief フェード時の色の設定
		 *
		 * @param color 設定する色
		 */
		void SetFadeColor(Col4 color) {
			m_color = color;
		}

		/**
		 * @brief フェードイン
		 */
		void FadeIn();

		/**
		 * @brief フェードアウト
		 */
		void FadeOut();

		/**
		 * @brief フェード完了までの時間設定
		 *
		 * @param time 時間(秒)
		 */
		void SetFadeTime(float time) {
			m_fadeTime = time;
		}

		/**
		 * @brief フェード完了までの時間取得
		 *
		 * @return フェード完了までの時間
		 */
		float GetFadeTime() {
			return m_fadeTime;
		}

		/**
		 * @brief 動作しているかのフラグ
		 *
		 * @return 動作中:true/停止中:false
		 */
		bool IsFadeActive() {
			return m_bActive;
		}
	};

}
//end basecross
