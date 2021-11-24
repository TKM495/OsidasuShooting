#pragma once
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	// 揃え方
	struct Anchor {
		// 垂直方向
		enum class Vertical {
			Top,
			Center,
			Bottom
		};
		// 水平方向
		enum class Horizontal {
			Left,
			Center,
			Right
		};

		Vertical vertical;
		Horizontal horizontal;

		Anchor() {
			this->vertical = Vertical::Top;
			this->horizontal = Horizontal::Left;
		}
		Anchor(const Vertical& vertical, const Horizontal& horizontal) {
			this->vertical = vertical;
			this->horizontal = horizontal;
		}
	};

	using Align = Anchor;

	// UI用のインターフェイス
	class UIInterface {
	public:
		UIInterface() {}
		~UIInterface() {}

		virtual TransformData GetTransformData() = 0;
		virtual Align GetAlign() = 0;
		virtual Anchor GetAnchor() = 0;
	private:
		//コピー禁止
		UIInterface(const UIInterface&) = delete;
		UIInterface& operator=(const UIInterface&) = delete;
		//ムーブ禁止
		UIInterface(const UIInterface&&) = delete;
		UIInterface& operator=(const UIInterface&&) = delete;
	};
}
