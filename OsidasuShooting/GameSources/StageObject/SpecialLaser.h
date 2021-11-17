/*!
@file   SpecialLaser.h
@brief  •KŽE‹Z
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "PlayerBase.h"

namespace basecross {
	class SpecialLaser : public StageObject {
	public:
		SpecialLaser(const shared_ptr<Stage>& stage) :
			StageObject(stage)
		{}
	};
}