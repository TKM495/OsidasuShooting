/*!
@file   MoveBlock.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "Block.h"

namespace basecross {
	class MoveBlock : public Block {
	// �N����
		// �N�������ǂ���
		bool m_isSetUp;

	// �ړ��֘A
		// ��������|�W�V����
		Vec3 m_markPosition[2];
		// �������Ă���̑ҋ@����
		float m_waitTime;

	// ���̑�����
		// �ݒu�ꏊ
		Vec3 m_setPosition;

	public:
		MoveBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData
		) :
			Block(stage, transformData),
			// �N����
			m_isSetUp(false),
			// �ړ��֘A
			m_markPosition{},
			m_waitTime(),
			// ���̑�����
			m_setPosition(0)
		{
			m_transformData = transformData;
		}

		MoveBlock(const shared_ptr<Stage>& stage,
			const TransformData transformData,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();
	};
}