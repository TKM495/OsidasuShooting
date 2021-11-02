#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
		: Component(gameObjectPtr), m_handle(-1), m_playSpeed(1)
	{
		// �}�l�[�W���[�̃|�C���^���擾
		m_manager = EfkInterface::GetInstance()->GetManager();
	}

	void EfkComponent::SetEffectResource(const wstring& key) {
		this->SetEffectResource(App::GetApp()->GetResource<EfkEffectResource>(key + EfkKey));
	}
	void EfkComponent::SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes) {
		m_effectData = effectRes->GetEffectData();
	}

	void EfkComponent::Play() {
		// �O��̃G�t�F�N�g���~
		Stop();
		// �Đ�
		m_handle = m_manager->Play(m_effectData, 0.0f, 0.0f, 0.0f);
		// �n���h�����Ȃ��Ɛݒ�ł��Ȃ��̂ł����ōĐ����x��ݒ�
		m_manager->SetSpeed(m_handle, m_playSpeed);
	}

	void EfkComponent::Stop() {
		if (m_handle != -1)
			m_manager->StopEffect(m_handle);
	}
	void EfkComponent::Pause() {
		if (m_handle != -1)
			// �|�[�Y���������瑱������Đ�
			m_manager->SetPaused(m_handle, !m_manager->GetPaused(m_handle));
	}

	void EfkComponent::SetPlaySpeed(float speed) {
		m_playSpeed = speed;
	}
}