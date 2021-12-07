/*!
@file   SoundManager.cpp
@brief  サウンドマネージャーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 初期化
	unique_ptr<SoundManager, SoundManager::Deleter> SoundManager::m_instance = nullptr;

	SoundManager::SoundManager()
		:m_manager(App::GetApp()->GetXAudio2Manager()),
		m_defaultVolume(0.5f), m_volumeRate(0.2f)
	{}

	shared_ptr<SoundItem> SoundManager::Play(const wstring& key) {
		return Play(key, 0, m_defaultVolume);
	}
	shared_ptr<SoundItem> SoundManager::Play(const wstring& key, size_t loopCount) {
		return Play(key, loopCount, m_defaultVolume);
	}
	shared_ptr<SoundItem> SoundManager::Play(const wstring& key, size_t loopCount, float volume) {
		return m_manager->Start(key, loopCount, volume * m_volumeRate);
	}

	void SoundManager::Stop(const shared_ptr<SoundItem>& soundItem) {
		m_manager->Stop(soundItem);
	}

	void SoundManager::Stop(const wstring& key) {
		auto resource = App::GetApp()->GetResource<AudioResource>(key);
		auto soundData = resource->GetSoundData();
		auto soundItem = m_manager->GetSoundItemVec();
		for (auto& item : soundItem)
		{
			if (item->m_SourceVoice != nullptr && soundData == item->m_AudioResource.lock()->GetSoundData())
			{
				Stop(item);
				return;
			}
		}
	}

	void SoundManager::StopAll() {
		auto soundItem = m_manager->GetSoundItemVec();
		for (auto& item : soundItem)
		{
			if (item->m_SourceVoice != nullptr)
			{
				Stop(item);
			}
		}
	}

	bool SoundManager::IsPlaying(const shared_ptr<SoundItem>& item) {
		if (!item) {
			return false;
		}
		if (item->m_SourceVoice) {
			XAUDIO2_VOICE_STATE state;
			bool isRunning;
			item->m_SourceVoice->GetState(&state);
			isRunning = (state.BuffersQueued > 0) != 0;
			return isRunning;
		}
		return false;
	}
}