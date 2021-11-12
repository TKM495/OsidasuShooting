/*!
@file TimeCounter.cpp
@brief ���Ԍv���N���X����
*/

#include "stdafx.h"
#include "TimeCounter.h"

namespace basecross {
	bool TimeCounter::Count() {
		auto elapsed = App::GetApp()->GetElapsedTime();
		if (m_elaspedTime >= m_intervalTime) {
			m_isTimeUp = true;
		}
		else {
			m_isTimeUp = false;
		}

		// �O�̂��ߎw�肵�����Ԃ��o�߂������~������
		if (!m_isTimeUp) {
			m_elaspedTime += elapsed;
		}
		else {
			m_elaspedTime = m_intervalTime;
		}
		return m_isTimeUp;
	}
}
//end basecross