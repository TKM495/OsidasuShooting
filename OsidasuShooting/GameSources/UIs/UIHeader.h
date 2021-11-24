#pragma once
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	// ������
	struct Anchor {
		// ��������
		enum class Vertical {
			Top,
			Center,
			Bottom
		};
		// ��������
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

	// UI�p�̃C���^�[�t�F�C�X
	class UIInterface {
	public:
		UIInterface() {}
		~UIInterface() {}

		virtual TransformData GetTransformData() = 0;
		virtual Align GetAlign() = 0;
		virtual Anchor GetAnchor() = 0;
	private:
		//�R�s�[�֎~
		UIInterface(const UIInterface&) = delete;
		UIInterface& operator=(const UIInterface&) = delete;
		//���[�u�֎~
		UIInterface(const UIInterface&&) = delete;
		UIInterface& operator=(const UIInterface&&) = delete;
	};
}
