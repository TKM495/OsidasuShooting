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
		Vec3 m_startPosition;
		Vec3 m_markPosition;
		//// ��������
		//bool m_posXorZ;
		// 2�_�̍�
		Vec3 m_moveRoot;
		// �������Ă���̑ҋ@����
		float m_waitTime;
		// �ҋ@��
		bool m_isWait;
		// �i�ނ��߂邩
		bool m_isReturnBlock;

	// ���̑�����
		// �ݒu�ꏊ
		Vec3 m_setPosition;

	public:
		MoveBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData,
			const Vec3 markPosition//,
			//const bool posXorZ
		) :
			Block(stage, transformData),
			// �N����
			m_isSetUp(false),
			// �ړ��֘A
			m_markPosition(markPosition),
			m_moveRoot(0),
			m_waitTime(0),
			m_isWait(false),
			m_isReturnBlock(false),
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
		void MovingBlock();
	};
}