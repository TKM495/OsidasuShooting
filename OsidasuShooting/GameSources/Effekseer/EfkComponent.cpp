#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
		: Component(gameObjectPtr), m_handle(-1), m_playSpeed(1)
	{
		m_manager = EfkInterface::GetInstance()->GetManager();
	}

	void EfkComponent::SetEffectResource(const wstring& key) {
		this->SetEffectResource(App::GetApp()->GetResource<EfkEffectResource>(key));
	}
	void EfkComponent::SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes) {
		m_effectData = effectRes->GetEffectData();
	}

	void EfkComponent::Play() {
		Stop();
		m_handle = m_manager->Play(m_effectData, 0.0f, 0.0f, 0.0f);
		m_manager->SetSpeed(m_handle, m_playSpeed);
		Debug::GetInstance()->Log(Util::IntToWStr(m_handle));
	}

	void EfkComponent::Stop() {
		if (m_handle != -1) {
			m_manager->StopEffect(m_handle);
		}
	}
	void EfkComponent::Pause() {
		m_manager->SetPaused(m_handle, !m_manager->GetPaused(m_handle));
	}

	void EfkComponent::SetPlaySpeed(float speed) {
		m_playSpeed = speed;
	}
}