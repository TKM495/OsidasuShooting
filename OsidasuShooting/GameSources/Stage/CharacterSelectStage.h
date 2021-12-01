#pragma once
#include "stdafx.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		// ÉrÉÖÅ[ÇÃçÏê¨
		void CreateViewLight();

		wstring m_charaName[4];
		float m_posOffsetX;
		float m_posOffsetY;
		float m_shiftMovePos;

	public:
		CharacterSelectStage(
		) :
			Stage(),
			m_charaName{},
			m_posOffsetX(-128.0f),
			m_posOffsetY(100.0f),
			m_shiftMovePos(200)
		{}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;

		void SetCharaName();
	};
}
