/*!
@file   Reflector.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "Block.h"

namespace basecross {

	class Reflector : public Block {
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
		Reflector(
			shared_ptr<Stage>& stage,
			const TransformData transformData 
		):
			Block(stage,transformData),
			// 起動中
			m_isSetUp(false),
			m_setReflectSpin(0),

			// その他項目
			m_setPosition(0),
			m_isReflect(false)
		{
			m_transformData = transformData;
		}

		Reflector(const shared_ptr<Stage>& stage,
			const TransformData transformData,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();

	};
}