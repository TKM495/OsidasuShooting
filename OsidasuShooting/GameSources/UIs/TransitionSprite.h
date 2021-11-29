#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class TransitionSprite :public BaseSingletonGameObject<TransitionSprite> {
	public:
		TransitionSprite(const shared_ptr<Stage>& stage)
			:BaseSingletonGameObject(stage)
		{}

		void OnCreate()override;
		void FadeIn() {
			GetFade()->FadeIn();
		}
		void FadeOut() {
			GetFade()->FadeOut();
		}
		shared_ptr<FadeComponent> GetFade() {
			return GetComponent<FadeComponent>();
		}
	};
}
