#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class OneShotUI :public BaseUI {
		enum class State {
			FadeIn,
			Normal,
			FadeOut
		};
		State m_state;

		// 寿命
		float m_lifeSpan;
		// テクスチャキー
		wstring m_textureKey;
		TimeCounter m_timer;
		shared_ptr<GameObject> m_owner;
	public:
		OneShotUI(const shared_ptr<Stage>& stage,
			const shared_ptr<GameObject>& owner,
			float lifeSpan, const wstring& texKey,
			const TransformData& transformData);

		void OnCreate()override;
		void OnUpdate()override;
	};
}
