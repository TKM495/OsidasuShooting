/*!
@file   BreakBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "Block.h"

namespace basecross {

	class BreakBlock : public Block {
		//起動中
			// 起動中かどうか
		bool m_isSetUp;

		// その他項目
			// 設置場所
		Vec3 m_setPosition;

	public:
		BreakBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData
		) :
			Block(stage, transformData),
			// 起動中
			m_isSetUp(false),

			// その他項目
			m_setPosition(0)
		{
			m_transformData = transformData;
		}

		BreakBlock(const shared_ptr<Stage>& stage,
			const TransformData transformData,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void SetUpAnimation();

	};
}