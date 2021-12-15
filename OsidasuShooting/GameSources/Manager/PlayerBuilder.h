#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class PlayerBuilder :public AdvancedGameObject {
		/**
		 * @brief ����^�C�v
		 */
		enum class OperationType {
			Manual,	// �蓮
			CPU		// CPU
		};
		// �v���C���[�ԍ�
		PlayerNumber m_playerNumber;
		// ����^�C�v
		OperationType m_operationType;
	public:
		PlayerBuilder(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
	};
}
