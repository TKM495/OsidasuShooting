/*!
@file   SoundManager.h
@brief  サウンドマネージャー
*/

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class SoundManager :public BaseSingleton<SoundManager> {
	private:
		// マネージャー
		shared_ptr<XAudio2Manager> m_manager;
	private: //シングルトン関係
		SoundManager() :m_manager(App::GetApp()->GetXAudio2Manager()) {}
		~SoundManager() {}
		friend class BaseSingleton<SoundManager>;
	public:
		/**
		 * @brief 再生
		 *
		 * @param key 再生したい音のキー
		 * @param loopCount ループ回数（0 = 1回再生）
		 * @param volume 音量
		 * @return サウンドアイテムのポインタ
		 */
		shared_ptr<SoundItem> Play(const wstring& key, size_t loopCount = 0, float volume = 0.3f);
		/**
		 * @brief 停止
		 *
		 * @param soundItem 停止するサウンドアイテムのポインタ
		 */
		void Stop(const shared_ptr<SoundItem>& soundItem);
		/**
		 * @brief 停止
		 *
		 * @param key 停止する音のキー
		 */
		void Stop(const wstring& key);
		/**
		 * @brief すべての音を停止
		 */
		void StopAll();
	};
}
