/*!
@file   BreakBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class BreakBlock : public AdvancedGameObject {
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
			const TransformData transformData/*,
			const float hp,
			const float wakeupTime*/
		) :
			AdvancedGameObject(stage),

			// ステータス
			m_hp(3),
			m_nowHp(0),
			m_wakeupTime(5),
			m_nowTime(0),

			// その他項目
			m_setPosition(0)
		{
			m_transformData = transformData;
		}

		BreakBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) {};

		//void SetUpAnimation();
		void BlockDamage(float damage);
	};
}