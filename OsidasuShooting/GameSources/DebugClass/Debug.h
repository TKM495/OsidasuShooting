/*!
@file   Debug.h
@brief  �f�o�b�O�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Debug :public GameObject {
	private:
		/**
		 * @brief ���O�̎��
		 */
		enum class Type {
			Normal,		// �ʏ�
			Warning,	// �x��
			Error		// �G���[
		};
		// ���O�̃f�[�^�{��
		vector<wstring> m_logData;
		// �\�����郍�O�̍ŏ��̃C���f�b�N�X
		int m_displayLogFirstIndex;
		// StringSprite�R���|�[�l���g
		shared_ptr<StringSprite> m_ssComp;
		// ���g�̃C���X�^���X
		static shared_ptr<Debug> m_ownInstance;

		/**
		 * @brief ���O�f�[�^�ɕϊ�
		 *
		 * @param type	�^�C�v
		 * @param text	�e�L�X�g
		 * @return 1�s���̃��O�̕�����
		 */
		wstring ConvertingToLogData(Type type, wstring text);
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
		 * @brief �ʏ�̃��O���o��
		 *
		 * @param text ���O�Ƃ��ďo��������
		 */
		void Log(const wstring& text);
		/**
		 * @brief �x���̃��O���o��
		 *
		 * @param text ���O�Ƃ��ďo��������
		 */
		void WarningLog(const wstring& text);
		/**
		 * @brief �G���[�̃��O���o��
		 *
		 * @param text ���O�Ƃ��ďo��������
		 */
		void ErrorLog(const wstring& text);

		/**
		 * @brief Debug�̃C���X�^���X���擾
		 *
		 * @return shared_ptr<Debug>
		 */
		static shared_ptr<Debug> GetInstance();
	};
}
//end basecross