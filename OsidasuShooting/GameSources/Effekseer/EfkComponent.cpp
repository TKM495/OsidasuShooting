/*!
@file   EfkComponent.cpp
@brief  Effekseer���g�p���邽�߂̃R���|�[�l���g�̎���
*/

#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
		: Component(gameObjectPtr), m_handle(-1), m_playSpeed(1),
		m_scale(Vec3(1.0f)), m_rotation(Vec3(0.0f))
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
		auto pos = GetGameObject()->GetComponent<Transform>()->GetPosition();
		// �Đ�
		m_handle = m_manager->Play(m_effectData, pos.x, pos.y, pos.z);
		// �n���h�����Ȃ��Ɛݒ�ł��Ȃ��̂ł����ōĐ����x��ݒ�
		m_manager->SetSpeed(m_handle, m_playSpeed);
		// �X�P�[����ݒ�
		m_manager->SetScale(m_handle, m_scale.x, m_scale.y, m_scale.z);
		// ��]��ݒ�
		auto rad = Utility::ConvertDegVecToRadVec(m_rotation);
		m_manager->SetRotation(m_handle, rad.x, rad.y, rad.z);
	}

	void EfkComponent::Stop() {
		if (IsPlaying())
			m_manager->StopEffect(m_handle);
	}
	void EfkComponent::Pause() {
		if (IsPlaying())
			// �|�[�Y���������瑱������Đ�
			m_manager->SetPaused(m_handle, !m_manager->GetPaused(m_handle));
	}

	void EfkComponent::SetPlaySpeed(float speed) {
		m_playSpeed = speed;
	}

	void EfkComponent::AddLocation(const Vec3& position) {
		if (!IsPlaying())
			return;
		m_manager->AddLocation(m_handle, Effekseer::Vector3D(position.x, position.y, position.z));
	}

	void EfkComponent::SetRotation(const Vec3& rotation) {
		m_rotation = rotation;
	}

	void EfkComponent::SetScale(const Vec3& scale) {
		m_scale = scale;
	}

	bool EfkComponent::IsPlaying() {
		return (m_handle != -1);
	}
}