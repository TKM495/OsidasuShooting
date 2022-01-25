/*!
@file ResultSprite.h
@brief リザルトで使うスプライト
*/

#pragma once
#include "stdafx.h"
#include "UIs/CharaSelectUIs.h"

namespace basecross {

	class ResultWinOrDrowSprite : public BaseSprite {
		Vec3 m_setPos;
		bool m_win;

	public:
		ResultWinOrDrowSprite(
			const shared_ptr<Stage>& stage,
			Vec3 position,
			bool win
		) :
			BaseSprite(stage, position),
			m_setPos(position),
			m_win(win)
		{}

		virtual ~ResultWinOrDrowSprite() {};

		void OnCreate() override;
		void OnUpdate() {};
	};

	class KillIcon : public BaseSprite {
		Vec3 m_setPos;
	public:
		KillIcon(
			const shared_ptr<Stage>& stage,
			Vec3 position
		):
			BaseSprite(stage,position),
			m_setPos(position)
		{}
		void OnCreate() override;
	};

	class DeadIcon : public BaseSprite {
		Vec3 m_setPos;
	public:
		DeadIcon(
			const shared_ptr<Stage>& stage,
			Vec3 position
		):
			BaseSprite(stage,position),
			m_setPos(position)
		{}
		void OnCreate() override;
	};
}