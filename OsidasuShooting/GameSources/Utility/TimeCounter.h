/*!
@file TimeCounter.h
@brief 時間計測クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeCounter {
		float m_delta;
		float m_countTime;
	public:
		TimeCounter()
			:m_delta(0.0f), m_countTime(0.0f)
		{}
		//数える時間を設定する関数
		void SetCountTime(float time) {
			m_countTime = time;
		}
		float GetCountTime() {
			return m_countTime;
		}
		//現在の時間の取得
		float GetTime() {
			return m_delta;
		}
		//タイマーのリセット
		void Reset() {
			m_delta = 0.0f;
		}
		//カウント
		bool Count();
		bool Count(float offset);
	};
}
//end basecross