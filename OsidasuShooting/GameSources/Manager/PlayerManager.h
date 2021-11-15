/*!
@file   PlayerManager.h
@brief  �v���C���[���Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	class PlayerManager {
		vector<PlayerBase> m_player;
	public:
		void AddPlayer(const shared_ptr<PlayerBase>& playerPtr);
	};
}
