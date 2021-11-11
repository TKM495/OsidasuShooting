/*!
@file TimeCounter.cpp
@brief 時間計測クラス実体
*/

#include "stdafx.h"
#include "TimeCounter.h"

namespace basecross {
	bool TimeCounter::Count() {
		return Count(0.0f);
	}
	bool TimeCounter::Count(float offset) {
		auto elapsed = App::GetApp()->GetElapsedTime();
		bool flg = false;
		if (m_countTime - offset < m_delta) {
			flg = true;
		}
		else {
			flg = false;
		}

		//念のため指定した時間が経過したら停止させる
		if (m_countTime >= m_delta) {
			m_delta += elapsed;
		}
		return flg;
	}
}
//end basecross