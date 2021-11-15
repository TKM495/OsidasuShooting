/*!
@file BattlePlayersUIs.h
@brief ÉvÉåÉCÉÑÅ[èÓïÒ
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class BattlePlayersUIs : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec2 m_startPos;
		wstring m_textureKey;

	public:
		BattlePlayersUIs(const shared_ptr<Stage>& stage,const wstring& TextureKey,bool Trace,
			const Vec2& StartScale,const Vec2& StartPos) :
			GameObject(stage),
			m_textureKey(TextureKey),
			m_trace(Trace),
			m_startScale(StartScale),
			m_startPos(StartPos)

		{}

		void OnCreate() override;
		void OnUpDate() {};
	};
}