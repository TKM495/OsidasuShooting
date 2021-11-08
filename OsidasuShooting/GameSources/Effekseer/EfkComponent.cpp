/*!
@file   EfkComponent.cpp
@brief  Effekseerを使用するためのコンポーネントの実体
*/

#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkComponent::EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
		: Component(gameObjectPtr), m_handle(-1), m_playSpeed(1),
		m_scale(Vec3(1.0f)), m_rotation(Vec3(0.0f))
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
		auto pos = GetGameObject()->GetComponent<Transform>()->GetPosition();
		// 再生
		m_handle = m_manager->Play(m_effectData, pos.x, pos.y, pos.z);
		// ハンドルがないと設定できないのでここで再生速度を設定
		m_manager->SetSpeed(m_handle, m_playSpeed);
		// スケールを設定
		m_manager->SetScale(m_handle, m_scale.x, m_scale.y, m_scale.z);
		// 回転を設定
		auto rad = Utility::ConvertDegVecToRadVec(m_rotation);
		m_manager->SetRotation(m_handle, rad.x, rad.y, rad.z);
	}

	void EfkComponent::Stop() {
		if (IsPlaying())
			m_manager->StopEffect(m_handle);
	}
	void EfkComponent::Pause() {
		if (IsPlaying())
			// ポーズ中だったら続きから再生
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