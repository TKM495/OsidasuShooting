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