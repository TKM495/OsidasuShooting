/*!
@file PlayerCharaPicture.h
@brief �v���C���[�L�����̃C���[�W
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "UIs/CharaSelectUIs.h"

namespace basecross
{
	// �i�ނ̕����̉摜
	class PlayerCharaPicture : public BaseSprite {
		Vec3 m_setPos;
		int m_gamePadIDs;
		int m_charaID;
	public:
		PlayerCharaPicture(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition,
			int characterNumber,
			int gamePadID
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_charaID(characterNumber),
			m_gamePadIDs(gamePadID)
		{}
		void OnCreate() override;
		void OnUpdate() override;
		wstring PlayerCharacter();
		wstring PlayerNumber();
		
		void DrawCharacter(int gamePadID);
	};
}