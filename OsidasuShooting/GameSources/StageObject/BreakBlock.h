/*!
@file   BreakBlock.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "Block.h"

namespace basecross {

	class BreakBlock : public Block {
		//�N����
			// �N�������ǂ���
		bool m_isSetUp;

		// ���̑�����
			// �ݒu�ꏊ
		Vec3 m_setPosition;

	public:
		BreakBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData
		) :
			Block(stage, transformData),
			// �N����
			m_isSetUp(false),

			// ���̑�����
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