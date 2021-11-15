/*!
@file TimeCounter.h
@brief 時間計測クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeCounter {
		// 設定された時間
		float m_intervalTime;
		// 経過時間
		float m_elaspedTime;
		// 設定した時間を経過しているか？
		bool m_isTimeUp;
	public:
		TimeCounter(float interval)
			: m_intervalTime(interval), m_elaspedTime(0.0f), m_isTimeUp(false)
		{}
		//タイマーのリセット
		void Reset() {
			m_elaspedTime = 0.0f;
			m_isTimeUp = false;
		}
		//カウント
		bool Count();

		bool IsTimeUp() {
			return m_isTimeUp;
		}

		void SetIntervalTime(float interval) {
			m_intervalTime = interval;
		}

		// 経過時間 / 設定された時間 の割合
		float GetTimeRate() {
			return m_elaspedTime / m_intervalTime;
		}

		// (1.0f - 経過時間 / 設定された時間)
		float GetInverseTimeRate() {
			return 1 - GetTimeRate();
		}

		// 残り時間
		float GetLeftTime() {
			return m_intervalTime - m_elaspedTime;
		}

		// 経過時間
		float GetElaspedTime() {
			return m_elaspedTime;
		}
	};
}
//end basecross