#pragma once
#include "stdafx.h"
#include "UIs/SimpleSprite.h"

namespace basecross {
	class CircleShadow :public Component {
		shared_ptr<BoardPoly> m_shadow;
		float m_scale;
	public:
		CircleShadow(const shared_ptr<GameObject>& gameObjectPtr,
			float scale);

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
