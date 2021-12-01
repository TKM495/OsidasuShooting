#pragma once
#include "stdafx.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		// �r���[�̍쐬
		void CreateViewLight();

		float m_shiftMovePos;
	public:
		CharacterSelectStage(
		) :
			Stage(),
			m_shiftMovePos(200)
		{}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;

		void SetCharaName();
	};
}
