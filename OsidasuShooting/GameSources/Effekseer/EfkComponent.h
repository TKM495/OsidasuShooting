#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	class EfkComponent : public Component {
		/**
		 * @brief É|Å[ÉYÇÇ«Ç§Ç∑ÇÈÇ©
		 */
		enum class PauseState {
			Play,	// çƒê∂
			Stop	// àÍéûí‚é~
		};

		EffectRef m_effectData;
		Handle m_handle;
	public:
		EfkComponent(const shared_ptr<GameObject>& gameObjectPtr)
			: Component(gameObjectPtr), m_handle(-1)
		{}
		~EfkComponent() {}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw()override {}

		void SetEffectResource(const wstring& key);
		void SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes);
		//void AddEffectResource(const wstring& key);

		void Play();
		//void Play(const wstring& Key);

		void Stop();
		void Pause(PauseState state);

		void SetPlaySpeed(int speed);
		void SetRotation(Vec3 rot);
	};
}
