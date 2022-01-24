/*!
@file   Block.h
@brief  �u���b�N�N���X
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class Block :public AdvancedGameObject {
	public:
		// �蓮�ǉ��p�R���X�g���N�^
		Block(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage)
		{
			m_transformData = transData;
		}
		// �I�u�W�F�N�g�r���_�[�p�̃R���X�g���N�^
		Block(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
	};

	class Bumper :public AdvancedGameObject {
		bool m_isAnimation;
	public:
		// �蓮�ǉ��p�R���X�g���N�^
		Bumper(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage), m_isAnimation(false)
		{
			m_transformData = transData;
		}
		// �I�u�W�F�N�g�r���_�[�p�̃R���X�g���N�^
		Bumper(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
		void OnUpdate()override;

		void PlayAnimation();
	};
}
