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
		// �蓮�ǉ��p�R���X�g���N�^
		Block(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage)
		{
			m_transformData = transData;
		}
		// �I�u�W�F�N�g�r���_�[�p�̃R���X�g���N�^
		Block(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
		void OnUpdate()override;
	};
}
