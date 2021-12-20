/*!
@file   MoveBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "Block.h"

namespace basecross {
	class MoveBlock : public Block {
	// 起動中
		// 起動中かどうか
		bool m_isSetUp;

	// 移動関連
		// 往復するポジション
		Vec3 m_markPosition[2];
		// 到着してからの待機時間
		float m_waitTime;

	// その他項目
		// 設置場所
		Vec3 m_setPosition;

	public:
		MoveBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData
		) :
			Block(stage, transformData),
			// 起動中
			m_isSetUp(false),
			// 移動関連
			m_markPosition{},
			m_waitTime(),
			// その他項目
			m_setPosition(0)
		{
			m_transformData = transformData;
		}

		MoveBlock(const shared_ptr<Stage>& stage,
			const TransformData transformData,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();
	};
}