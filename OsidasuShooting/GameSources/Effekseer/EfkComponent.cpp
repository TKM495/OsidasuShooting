/*!
@file   EfkComponent.cpp
@brief  Effekseer���g�p���邽�߂̃R���|�[�l���g�̎���
*/

#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
		:EfkComponent(gameObjectPtr, SpaceType::Local) {}

	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr, SpaceType useSpace)
		: Component(gameObjectPtr), m_playSpeed(1), m_useSpace(useSpace),
		m_coordinateType(CoordinateType::Relative)
	{
		// �}�l�[�W���[�̃|�C���^���擾
		m_manager = EfkInterface::GetInstance()->GetManager();
	}

	void EfkComponent::SetEffectResource(const wstring& key, const TransformData& offset, bool noStopLastEffect) {
		auto effectRes = App::GetApp()->GetResource<EfkEffectResource>(key + EfkKey);
		auto data = effectRes->GetEffectData();
		m_effectDataMap[key] = EfkData(data, offset, noStopLastEffect);
	}

	void EfkComponent::SetEffectResource(const wstring& key, const TransformData& offset) {
		SetEffectResource(key, offset, false);
	}

	void EfkComponent::SetEffectResource(const wstring& key) {
		SetEffectResource(key, TransformData(), false);
	}

	void EfkComponent::Play(const wstring& key) {
		auto& data = m_effectDataMap[key];
		if (!data.NoStopLastEffect) {
			// �O��̃G�t�F�N�g���~
			Stop(key);
		}
		Vec3 pos(0);
		switch (m_coordinateType)
		{
		case CoordinateType::Absolute:
			pos = data.Offset.Position;
			break;
		case CoordinateType::Relative:
			pos = GetGameObjectPosition() + data.Offset.Position;
			break;
		}

		// �Đ�
		data.Handle = m_manager->Play(data.EffectData, pos.x, pos.y, pos.z);
		// �n���h�����Ȃ��Ɛݒ�ł��Ȃ��̂ł����ōĐ����x��ݒ�
		m_manager->SetSpeed(data.Handle, m_playSpeed);
		// �X�P�[����ݒ�
		auto scale = data.Offset.Scale;
		m_manager->SetScale(data.Handle, scale.x, scale.y, scale.z);

		// ��]��ݒ�
		auto rad = Utility::ConvertDegVecToRadVec(data.Offset.Rotation);
		m_manager->SetRotation(data.Handle, rad.x, rad.y, rad.z);
	}

	void EfkComponent::Stop(const wstring& key) {
		if (IsPlaying(key))
			m_manager->StopEffect(m_effectDataMap[key].Handle);
	}
	void EfkComponent::Pause(const wstring& key) {
		auto handle = m_effectDataMap[key].Handle;
		if (IsPlaying(key))
			// �|�[�Y���������瑱������Đ�
			m_manager->SetPaused(handle, !m_manager->GetPaused(handle));
	}

	void EfkComponent::StopAll() {
		m_manager->StopAllEffects();
	}

	//void EfkComponent::SetPlaySpeed(float speed) {
	//	m_playSpeed = speed;
	//}

	//void EfkComponent::SetRotation(const Vec3& rotation) {
	//	m_rotation = rotation;
	//}

	//void EfkComponent::SetScale(const Vec3& scale) {
	//	m_scale = scale;
	//}

	bool EfkComponent::IsPlaying(const wstring& key) {
		return m_manager->Exists(m_effectDataMap[key].Handle);
	}

	bool EfkComponent::IsPlaying() {
		for (auto data : m_effectDataMap) {
			// �Đ����̃G�t�F�N�g�������true
			if (IsPlaying(data.first)) {
				return true;
			}
		}
		return false;
	}

	void EfkComponent::SyncPosition(const wstring& key) {
		if (!IsPlaying(key))
			return;
		auto data = m_effectDataMap[key];
		auto parentPosition = GetGameObjectPosition() + data.Offset.Position;
		m_manager->SetLocation(data.Handle, parentPosition.x, parentPosition.y, parentPosition.z);
	}

	Vec3 EfkComponent::GetGameObjectPosition() {
		auto transComp = GetGameObject()->GetComponent<Transform>();
		switch (m_useSpace)
		{
		case SpaceType::World:
			return transComp->GetWorldPosition();
		case SpaceType::Local:
			return transComp->GetPosition();
		default:
			return transComp->GetPosition();
		}
	}

	void EfkComponent::SetCoordinateType(CoordinateType coordinateType) {
		m_coordinateType = coordinateType;
	}
}