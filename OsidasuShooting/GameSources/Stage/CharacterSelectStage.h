#pragma once
#include "stdafx.h"
#include "UIs/CharaSelectUISprites.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		// ÉrÉÖÅ[ÇÃçÏê¨
		void CreateViewLight();

		wstring m_charaName[3];
		
		float m_posOffsetX;
		float m_posOffsetY;
		float m_shiftMovePos;

		bool m_ifEntryPlayer[4];

		//shared_ptr<CharacterIcon> charaIcon;
	public:
		CharacterSelectStage(
		) :
			Stage(),
			m_charaName{},
			m_posOffsetX(-18.0f),
			m_posOffsetY(-28.0f),
			m_shiftMovePos(180),
			m_ifEntryPlayer{false,false,false,false}
		{}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;

		void PlayerFreamPosition(Vec3 pos, int gamePadID);
		void PlayerCharacterSelect(Vec3 pos, int gamePadID);
		void PlayerSelectTriangle(Vec3 pos, Vec3 scl, int gamePadID);
		void SetCharaName();
	};
}
