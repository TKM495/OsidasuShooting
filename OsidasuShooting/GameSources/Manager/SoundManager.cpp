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

	shared_ptr<SoundItem> SoundManager::PlayLoop(const wstring& key) {
		return PlayLoop(key, m_defaultVolume);
	}

	shared_ptr<SoundItem> SoundManager::PlayLoop(const wstring& key, float volume) {
		return Play(key, XAUDIO2_LOOP_INFINITE, volume);
	}

	shared_ptr<SoundItem> SoundManager::Play(const wstring& key) {
		return Play(key, 0, m_defaultVolume);
	}
	shared_ptr<SoundItem> SoundManager::Play(const wstring& key, size_t loopCount) {
		return Play(key, loopCount, m_defaultVolume);
	}
	shared_ptr<SoundItem> SoundManager::Play(const wstring& key, size_t loopCount, float volume) {
		return m_manager->Start(key, loopCount, volume * m_volumeRate);
	}

	void SoundManager::InitPlayOverlap(const wstring& key, float interval) {
		TimeCounter timer(interval, true);
		m_timerMap[key] = make_shared<TimeCounter>(timer);
	}

	void SoundManager::PlayOverlap(const wstring& key) {
		PlayOverlap(key, m_defaultVolume);
	}

	void SoundManager::PlayOverlap(const wstring& key, float volume) {
		auto timer = m_timerMap[key];
		if (timer->Count()) {
			Play(key, 0, volume);
			timer->Reset();
		}
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