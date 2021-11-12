/*!
@file   PlayerManager.h
@brief  �v���C���[���Ǘ�����N���X
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

	// �v���C���[�C���^�[�t�F�C�X
	class PlayerInterface {
	public:
		PlayerInterface() {}
		~PlayerInterface() {}

		// �m�b�N�o�b�N
		virtual void KnockBack(Vec3 direction, float force) = 0;
	private:
		// �R�s�[�֎~
		PlayerInterface(const PlayerInterface&) = delete;
		PlayerInterface& operator=(const PlayerInterface&) = delete;
		// ���[�u�֎~
		PlayerInterface(const PlayerInterface&&) = delete;
		PlayerInterface& operator=(const PlayerInterface&&) = delete;
	};

	class PlayerManager {
	};
}
