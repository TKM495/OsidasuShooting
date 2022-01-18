/*!
@file PlayerCharaPicture.h
@brief プレイヤーキャラのイメージ
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"
#include "UIs/CharaSelectUIs.h"

namespace basecross
{
	// 進むの文字の画像
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