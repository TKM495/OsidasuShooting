/*!
@file BattlePlayersUIs.h
@brief ƒvƒŒƒCƒ„[î•ñ
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class ResultWinnerSprite : public GameObject {
		wstring m_textureKey;

	public:
		ResultWinnerSprite(const shared_ptr<Stage>& stage, const wstring& TextureKey
		) :
			GameObject(stage),
			m_textureKey(TextureKey)
		{}

		virtual ~ResultWinnerSprite() {};

		void OnCreate();
		void OnUpdate() {};

	};
}