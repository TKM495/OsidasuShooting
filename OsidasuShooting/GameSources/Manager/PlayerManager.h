/*!
@file   PlayerManager.h
@brief  プレイヤーを管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	// プレイヤーインターフェイス
	class PlayerInterface {
	public:
		PlayerInterface() {}
		~PlayerInterface() {}

		// ノックバック
		virtual void KnockBack(Vec3 direction, float force) = 0;
	private:
		// コピー禁止
		PlayerInterface(const PlayerInterface&) = delete;
		PlayerInterface& operator=(const PlayerInterface&) = delete;
		// ムーブ禁止
		PlayerInterface(const PlayerInterface&&) = delete;
		PlayerInterface& operator=(const PlayerInterface&&) = delete;
	};

	class PlayerManager {
	};
}
