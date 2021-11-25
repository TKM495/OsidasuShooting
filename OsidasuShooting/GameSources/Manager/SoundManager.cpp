/*!
@file   SoundManager.cpp
@brief  サウンドマネージャーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 初期化
	unique_ptr<SoundManager, SoundManager::Deleter> SoundManager::m_instance = nullptr;

	shared_ptr<SoundItem> SoundManager::Play(const wstring& key, size_t loopCount, float volume) {
		return m_manager->Start(key, loopCount, volume);
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
}