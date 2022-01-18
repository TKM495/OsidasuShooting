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
	class PlayerCharaUI : public BaseSprite {
		Vec3 m_setPos;
		int m_playerNumebr;
	public:
		PlayerCharaUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition,
			int playerNumber
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_playerNumebr(playerNumber)
		{}
		void OnCreate() override;
		void OnUpdate() override;
	};
}