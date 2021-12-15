#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class PlayerBuilder :public AdvancedGameObject {
		/**
		 * @brief 操作タイプ
		 */
		enum class OperationType {
			Manual,	// 手動
			CPU		// CPU
		};
		// プレイヤー番号
		PlayerNumber m_playerNumber;
		// 操作タイプ
		OperationType m_operationType;
	public:
		PlayerBuilder(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
	};
}
