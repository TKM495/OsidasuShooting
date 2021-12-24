/*!
@file   BreakBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "Block.h"
#include "JonyMd/CountDown.h"

namespace basecross {
	class BreakBlock : public Block {
	//起動中
		// 起動中かどうか
		bool m_isSetUp;

	// ステータス
		// ブロックのHP
		float m_hp;
		float m_nowHp;

		// 復活時間
		float m_wakeupTime;
		float m_nowTime;
	// その他項目
		// 設置場所
		Vec3 m_setPosition;

	public:
		BreakBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData,
			const float hp,
			const float wakeupTime
		) :
			Block(stage, transformData),
			// 起動中
			m_isSetUp(false),

			// ステータス
			m_hp(hp),
			m_nowHp(0),
			m_wakeupTime(wakeupTime),
			m_nowTime(0),

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
		void OnCollisionEnter(shared_ptr<GameObject>& other) {};

		void SetUpAnimation();
		void BlockDamage(float damage);

	};
}