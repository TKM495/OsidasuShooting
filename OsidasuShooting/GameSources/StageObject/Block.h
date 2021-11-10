/*!
@file   Block.h
@brief  ブロッククラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Block :public StageObject {
	public:
		// 手動追加用コンストラクタ
		Block(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage)
		{
			m_transformData = transData;
		}
		// オブジェクトビルダー用のコンストラクタ
		Block(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
		void OnUpdate()override;
	};
}
