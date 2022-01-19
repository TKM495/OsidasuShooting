#pragma once
#include "stdafx.h"
#include "UIs/SimpleSprite.h"

namespace basecross {
	class CircleShadow :public Component {
		shared_ptr<BoardPoly> m_shadow;
	public:
		CircleShadow(const shared_ptr<GameObject>& gameObjectPtr);

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
