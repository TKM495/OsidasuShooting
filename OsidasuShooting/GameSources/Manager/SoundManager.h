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
		// デフォルトの音量
		float m_defaultVolume;
		// 音量の割合（1.0f = 100%）
		float m_volumeRate;

		/**
		 * @brief 再生中か
		 *
		 * @param item 判定するアイテム
		 * @return trueなら再生中
		 */
		bool IsPlaying(const shared_ptr<SoundItem>& item);
	private: //シングルトン関係
		SoundManager();
		~SoundManager() {}
		friend class BaseSingleton<SoundManager>;
	public:
		/**
		 * @brief 再生
		 *
		 * @param key 再生したい音のキー
		 * @return サウンドアイテムのポインタ
		 */
		shared_ptr<SoundItem> Play(const wstring& key);
		/**
		 * @brief 再生
		 *
		 * @param key 再生したい音のキー
		 * @param loopCount ループ回数（0 = 1回再生:XAUDIO2_LOOP_INFINITE = ∞）
		 * @return サウンドアイテムのポインタ
		 */
		shared_ptr<SoundItem> Play(const wstring& key, size_t loopCount);
		/**
		 * @brief 再生
		 *
		 * @param key 再生したい音のキー
		 * @param loopCount ループ回数（0 = 1回再生:XAUDIO2_LOOP_INFINITE = ∞）
		 * @param volume 音量
		 * @return サウンドアイテムのポインタ
		 */
		shared_ptr<SoundItem> Play(const wstring& key, size_t loopCount, float volume);
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
