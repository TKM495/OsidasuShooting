/*!
@file TimeCounter.h
@brief ���Ԍv���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeCounter {
		// �ݒ肳�ꂽ����
		float m_intervalTime;
		// �o�ߎ���
		float m_elaspedTime;
		// �ݒ肵�����Ԃ��o�߂��Ă��邩�H
		bool m_isTimeUp;
		// �����[�h�^�C�}�[���i�����[�h�^�C�}�[�F�ŏ�����Count��true�̏�Ԃ̃^�C�}�[�j
		bool m_isReloadTimer;
	public:
		TimeCounter(float interval, bool isReloadTimer = false)
			: m_intervalTime(interval), m_elaspedTime(0.0f), m_isTimeUp(false),
			m_isReloadTimer(isReloadTimer)
		{
			if (isReloadTimer)
				m_elaspedTime = m_intervalTime;
		}
		//�^�C�}�[�̃��Z�b�g
		void Reset() {
			m_elaspedTime = 0.0f;
			m_isTimeUp = false;
		}
		//�J�E���g
		bool Count();

		bool IsTimeUp() {
			return m_isTimeUp;
		}

		void SetIntervalTime(float interval) {
			m_intervalTime = interval;
		}

		// �o�ߎ��� / �ݒ肳�ꂽ���� �̊���
		float GetTimeRate() {
			return m_elaspedTime / m_intervalTime;
		}

		// (1.0f - �o�ߎ��� / �ݒ肳�ꂽ����)
		float GetInverseTimeRate() {
			return 1 - GetTimeRate();
		}

		// �c�莞��
		float GetLeftTime() {
			return m_intervalTime - m_elaspedTime;
		}

		// �o�ߎ���
		float GetElaspedTime() {
			return m_elaspedTime;
		}
	};
}
//end basecross