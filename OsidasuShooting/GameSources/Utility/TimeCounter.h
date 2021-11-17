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
		// �����[�h�^�C�}�[��
		//�i�����[�h�^�C�}�[�F�ŏ�����m_isTimeUp��true�̏�Ԃ̃^�C�}�[�j
		bool m_isReloadTimer;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param interval �v�����鎞��
		 * @param isReloadTimer �����[�h�^�C�}�[��
		 */
		TimeCounter(float interval, bool isReloadTimer = false)
			: m_intervalTime(interval), m_elaspedTime(0.0f), m_isTimeUp(false),
			m_isReloadTimer(isReloadTimer)
		{
			if (isReloadTimer)
				m_elaspedTime = m_intervalTime;
		}
		/**
		 * @brief �^�C�}�[�̃��Z�b�g
		 */
		void Reset() {
			m_elaspedTime = 0.0f;
			m_isTimeUp = false;
		}
		/**
		 * @brief �^�C�}�[�̃��Z�b�g�i�V���Ɍv�����Ԃ�ݒ�j
		 *
		 * @param interval �v�����鎞��
		 */
		void Reset(float interval) {
			m_intervalTime = interval;
			m_elaspedTime = 0.0f;
			m_isTimeUp = false;
		}

		/**
		 * @brief �J�E���g
		 *
		 * @return true:�o�߂���/false:�o�߂��Ă��Ȃ�
		 */
		bool Count();

		/**
		 * @brief �ݒ肵�����Ԃ��o�߂�����
		 *
		 * @return true:�o�߂���/false:�o�߂��Ă��Ȃ�
		 */
		bool IsTimeUp() {
			return m_isTimeUp;
		}

		/**
		 * @brief �v�����Ԃ�ݒ�
		 *
		 * @param interval �v������
		 */
		void SetIntervalTime(float interval) {
			m_intervalTime = interval;
		}

		/**
		 * @brief �o�ߎ��� / �ݒ肳�ꂽ���� �̊������擾
		 *
		 * @return float �o�ߎ��� / �ݒ肳�ꂽ���� �̊���
		 */
		float GetTimeRate() {
			return m_elaspedTime / m_intervalTime;
		}

		/**
		 * @brief (1.0f - �o�ߎ��� / �ݒ肳�ꂽ����)���擾
		 *
		 * @return float (1.0f - �o�ߎ��� / �ݒ肳�ꂽ����)
		 */
		float GetInverseTimeRate() {
			return 1 - GetTimeRate();
		}

		/**
		 * @brief �c�莞�Ԃ��擾
		 *
		 * @return float �c�莞��
		 */
		float GetLeftTime() {
			return m_intervalTime - m_elaspedTime;
		}

		/**
		 * @brief �o�ߎ��Ԃ��擾
		 *
		 * @return float �o�ߎ���
		 */
		float GetElaspedTime() {
			return m_elaspedTime;
		}
	};
}
//end basecross