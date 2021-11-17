/*!
@file   SpecialLaser.h
@brief  •KŽE‹Z
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "PlayerBase.h"

namespace basecross {

	class SpecialSkill : public StageObject {
		float m_speed;
		float m_lifeSpan;
		float m_knokBackAmount;
		Vec3 m_distance;
		weak_ptr<PlayerBase> m_owner;

	public:
		SpecialSkill(
			const shared_ptr<Stage>& stage,
			const weak_ptr<PlayerBase>& owner,
			const Vec3& position,
			const Vec3& direction) :
			StageObject(stage),
			m_speed(0),
			m_lifeSpan(0),
			m_knokBackAmount(0),
			m_distance(0)
		{}
	};
}