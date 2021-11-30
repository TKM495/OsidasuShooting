/*!
@file   SoundManager.h
@brief  �T�E���h�}�l�[�W���[
*/

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class SoundManager :public BaseSingleton<SoundManager> {
	private:
		// �}�l�[�W���[
		shared_ptr<XAudio2Manager> m_manager;
		// �f�t�H���g�̉���
		float m_defaultVolume;
	private: //�V���O���g���֌W
		SoundManager()
			:m_manager(App::GetApp()->GetXAudio2Manager()),
			m_defaultVolume(0.2f)
		{}
		~SoundManager() {}
		friend class BaseSingleton<SoundManager>;
	public:
		/**
		 * @brief �Đ�
		 *
		 * @param key �Đ����������̃L�[
		 * @return �T�E���h�A�C�e���̃|�C���^
		 */
		shared_ptr<SoundItem> Play(const wstring& key);
		/**
		 * @brief �Đ�
		 *
		 * @param key �Đ����������̃L�[
		 * @param loopCount ���[�v�񐔁i0 = 1��Đ��j
		 * @return �T�E���h�A�C�e���̃|�C���^
		 */
		shared_ptr<SoundItem> Play(const wstring& key, size_t loopCount);
		/**
		 * @brief �Đ�
		 *
		 * @param key �Đ����������̃L�[
		 * @param loopCount ���[�v�񐔁i0 = 1��Đ��j
		 * @param volume ����
		 * @return �T�E���h�A�C�e���̃|�C���^
		 */
		shared_ptr<SoundItem> Play(const wstring& key, size_t loopCount, float volume);
		/**
		 * @brief ��~
		 *
		 * @param soundItem ��~����T�E���h�A�C�e���̃|�C���^
		 */
		void Stop(const shared_ptr<SoundItem>& soundItem);
		/**
		 * @brief ��~
		 *
		 * @param key ��~���鉹�̃L�[
		 */
		void Stop(const wstring& key);
		/**
		 * @brief ���ׂẲ����~
		 */
		void StopAll();
	};
}
