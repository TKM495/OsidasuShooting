#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
		: Component(gameObjectPtr), m_handle(-1), m_playSpeed(1)
	{
		// マネージャーのポインタを取得
		m_manager = EfkInterface::GetInstance()->GetManager();
	}

	void EfkComponent::SetEffectResource(const wstring& key) {
		this->SetEffectResource(App::GetApp()->GetResource<EfkEffectResource>(key + EfkKey));
	}
	void EfkComponent::SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes) {
		m_effectData = effectRes->GetEffectData();
	}

	void EfkComponent::Play() {
		// 前回のエフェクトを停止
		Stop();
		// 再生
		m_handle = m_manager->Play(m_effectData, 0.0f, 0.0f, 0.0f);
		// ハンドルがないと設定できないのでここで再生速度を設定
		m_manager->SetSpeed(m_handle, m_playSpeed);
	}

	void EfkComponent::Stop() {
		if (m_handle != -1)
			m_manager->StopEffect(m_handle);
	}
	void EfkComponent::Pause() {
		if (m_handle != -1)
			// ポーズ中だったら続きから再生
			m_manager->SetPaused(m_handle, !m_manager->GetPaused(m_handle));
	}

	void EfkComponent::SetPlaySpeed(float speed) {
		m_playSpeed = speed;
	}
}