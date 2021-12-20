/*!
@file   Reflector.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "Block.h"
namespace basecross {

	class Reflector : public Block {
	public:
		Reflector(
			shared_ptr<Stage>& stage,
			const TransformData transformData 
		):
			Block(stage,transformData)
		{
			m_transformData = transformData;
		}

		Reflector(
			const shared_ptr<Stage>& stage,
			const TransformData transformData,
			const wstring& line);

		void OnCreate()override;
		void OnUpdate()override;
	};
}