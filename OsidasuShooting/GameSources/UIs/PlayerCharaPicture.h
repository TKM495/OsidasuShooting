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
	public:
		PlayerCharaUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};
}