/*!
@file   ReflectorBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class ReflectorBlock : public AdvancedGameObject {
		//起動中
			// 起動中かどうか
		bool m_isSetUp;
		// 起動中アニメーション
		float m_setReflectSpin;

		// その他項目
			// 設置場所
		Vec3 m_setPosition;
		// 反射が出来るかどうか
		bool m_isReflect;

	public:
		ReflectorBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData
		) :
			AdvancedGameObject(stage),
			// 起動中
			m_isSetUp(false),
			m_setReflectSpin(0),

			// その他項目
			m_setPosition(0),
			m_isReflect(false)
		{
			m_transformData = transformData;
		}

		ReflectorBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();
	};
}