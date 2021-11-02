#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	class EfkComponent : public Component {
		EffectRef m_effectData;
		Handle m_handle;
		ManagerRef m_manager;
		float m_playSpeed;
	public:
		EfkComponent(const shared_ptr<GameObject>& gameObjectPtr);
		~EfkComponent() {}

		void OnCreate() override {}
		void OnUpdate() override {}
		void OnDraw()override {}

		void SetEffectResource(const wstring& key);
		void SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes);

		void Play();
		void Stop();
		void Pause();

		void SetPlaySpeed(float speed);
	};
}
