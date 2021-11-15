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
		// リロードタイマーか（リロードタイマー：最初からCountがtrueの状態のタイマー）
		bool m_isReloadTimer;
	public:
		TimeCounter(float interval, bool isReloadTimer = false)
			: m_intervalTime(interval), m_elaspedTime(0.0f), m_isTimeUp(false),
			m_isReloadTimer(isReloadTimer)
		{
			if (isReloadTimer)
				m_elaspedTime = m_intervalTime;
		}
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