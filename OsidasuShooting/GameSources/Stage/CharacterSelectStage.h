#pragma once
#include "stdafx.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		// �r���[�̍쐬
		void CreateViewLight();
	public:
		CharacterSelectStage() :Stage() {}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
