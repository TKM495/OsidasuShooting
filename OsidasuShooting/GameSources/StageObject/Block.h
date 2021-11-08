/*!
@file   Block.h
@brief  �u���b�N�N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Block :public StageObject {
	public:
		Block(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage)
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
