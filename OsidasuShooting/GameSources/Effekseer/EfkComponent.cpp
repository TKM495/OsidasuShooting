#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void EfkComponent::OnCreate() {
	}

	void EfkComponent::OnUpdate() {
	}

	void EfkComponent::SetEffectResource(const wstring& key) {
		this->SetEffectResource(App::GetApp()->GetResource<EfkEffectResource>(key));
	}
	void EfkComponent::SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes) {
		m_effectData = effectRes->GetEffectData();
	}

	//void EfkComponent::AddEffectResource(const wstring& key){}

	void EfkComponent::Play() {
		auto iface = EfkInterface::GetInstance();
		if (iface) {
			auto manager = iface->GetManager();
			manager->StopEffect(m_handle);
			m_handle = manager->Play(m_effectData, 0.0f, 0.0f, 0.0f);
			Debug::GetInstance()->Log(Util::IntToWStr(m_handle));
		}
	}
	//void EfkComponent::Play(const wstring& Key) {
	//}

	void EfkComponent::Stop() {
		//auto shptr = m_EfkInterface.lock();
		//if (shptr && m_Handle != -1) {
		//	shptr->m_Manager->StopEffect(m_Handle);
		//}
	}
	void EfkComponent::Pause(PauseState state) {
	}

	void EfkComponent::SetPlaySpeed(int speed) {
	}
	void EfkComponent::SetRotation(Vec3 rot) {
	}
}