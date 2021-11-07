/*!
@file   Debug.h
@brief  �f�o�b�O�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Debug :public GameObject {
	private:
		// ���O�̃f�[�^�{��
		vector<wstring> m_logData;
		// �\�����郍�O�̍ŏ��̃C���f�b�N�X
		int m_displayLogFirstIndex;
		// StringSprite�R���|�[�l���g
		shared_ptr<StringSprite> m_ssComp;
		// ���g�̃C���X�^���X
		static shared_ptr<Debug> m_ownInstance;

		/**
		 * @brief ���O��o�^
		 *
		 * @param text	�e�L�X�g
		 */
		void RegisterLog(const wstring& test);
		/**
		 * @brief ���݂̎��Ԃ𕶎���Ŏ擾
		 *
		 * @return ���݂̎��Ԃ̕�����
		 */
		wstring GetNowTimeString();
		/**
		 * @brief �V�X�e���̏��𕶎���Ŏ擾
		 *
		 * @return �V�X�e���̏��(������)
		 */
		wstring GetSystemInfo();
		/**
		 * @brief �r�����擾
		 *
		 * @return 1�s���̌r���̕�����
		 */
		wstring BorderInsertion();
	private: // �ȉ��ݒ�
		// �\�����郍�O�̍ő吔
		int m_maxLogCount;
		// ���O�̐���\�����邩
		bool m_isDisplayForCount;
		// �w�i��\�����邩
		bool m_isShowBackground;
	public:
		Debug(const shared_ptr<Stage>& stage)
			:GameObject(stage), m_displayLogFirstIndex(0),
			// �ȉ��ݒ�
			m_maxLogCount(18),
			m_isDisplayForCount(true),
			m_isShowBackground(false)
		{}
		void OnCreate();
		void OnUpdate();

		/**
		 * @brief ���O���o��
		 *
		 * @param text ���O�Ƃ��ďo��������
		 */
		void Log(const wstring& text);
		/**
		 * @brief ���O���o��
		 *
		 * @param value ���O�Ƃ��ďo�͂���l
		 */
		void Log(int value);
		/**
		 * @brief ���O���o��
		 *
		 * @param value ���O�Ƃ��ďo�͂���l
		 */
		void Log(float value);
		/**
		 * @brief ���O���o��
		 *
		 * @param value ���O�Ƃ��ďo�͂���l
		 */
		void Log(const Vec2& value);
		/**
		 * @brief ���O���o��
		 *
		 * @param value ���O�Ƃ��ďo�͂���l
		 */
		void Log(const Vec3& value);

		/**
		 * @brief Debug�̃C���X�^���X���擾
		 *
		 * @return shared_ptr<Debug>
		 */
		static shared_ptr<Debug> GetInstance();
	};
}
//end basecross