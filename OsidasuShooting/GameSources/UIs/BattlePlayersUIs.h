/*!
@file BattlePlayersUIs.h
@brief プレイヤー情報
*/

#pragma once
#include "stdafx.h"
#include "BaseUI.h"

namespace basecross
{
	class BattlePlayersUIs : public BaseUI {
		wstring m_textureKey;
		float m_objIconSize;
		int m_iconNumber;
		Vec3 m_position;

		int m_number;
		vector<VertexPositionColorTexture> vertices;

	public:
		BattlePlayersUIs(const shared_ptr<Stage>& stage,
			const wstring& TextureKey, 
			int iconNum, 
			Vec3 Pos
		) :
			BaseUI(stage, TransformData()),
			m_textureKey(TextureKey),
			m_iconNumber(iconNum),
			m_position(Pos),
			m_number(),
			m_objIconSize()

		{}

		void OnCreate() override;
		void OnUpDate() {};

		void PlayersNumberUICreate();

		void PlayersIconUICreate(int value);

		// プレイヤーのアイコンを切り出すための物
		// CirecleIcon = 0
		// Player 1  = 1
		// Player 2  = 2
		// Player 3  = 3
		// Player 4  = 4
		// CPUPlayer = 5
		// Crown = 6
		void SetPlayerNumValue(int value);
	};


	class BombIcon : public BaseSprite {
		Vec3 m_setPos;
	public:
		BombIcon(
			const shared_ptr<Stage>& stage,
			Vec3 position
		) :
			BaseSprite(stage, position),
			m_setPos(position)
		{}
		void OnCreate() override;
	};
}