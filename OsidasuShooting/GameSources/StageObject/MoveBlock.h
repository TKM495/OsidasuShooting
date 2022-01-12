/*!
@file   MoveBlock.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class MoveBlock : public AdvancedGameObject {
	public:
		// �u���b�N�̎��
		enum class BlockType {
			Normal,
			Bumper,
			Reflector
		};
	private:
		// �ړ��֘A
			// ��������|�W�V����
		Vec3 m_startPosition;
		Vec3 m_markPosition;
		//// ��������
		//bool m_posXorZ;
		// 2�_�̍�
		Vec3 m_moveRoot;
		// �ړ�
		float m_totalTime;
		// �������Ă���̑ҋ@����
		float m_waitTime;
		// �ҋ@��
		bool m_isWait;
		// �i�ނ��߂邩
		bool m_isGotoMarkPos;

		// ���̑�����
			// �ݒu�ꏊ
		Vec3 m_setPosition;

		// �u���b�N�̃^�C�v
		BlockType m_type;
		// �u���b�N�̃I�u�W�F�N�g
		shared_ptr<AdvancedGameObject> m_block;
		// �ړ����x
		float m_moveSpeed;
		// �ҋ@����
		float m_latency;
	public:
		MoveBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData,
			const Vec3 markPosition,
			BlockType type//,
			//const bool posXorZ
		) :
			AdvancedGameObject(stage),
			// �ړ��֘A
			m_markPosition(markPosition),
			m_moveRoot(0),
			m_totalTime(0),
			m_waitTime(0),
			m_isWait(false),
			m_isGotoMarkPos(false),
			// ���̑�����
			m_setPosition(0),
			m_type(type),
			m_moveSpeed(1.0f),
			m_latency(1.0f)
		{
			m_transformData = transformData;
		}

		MoveBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void MovingBlock();
		void MoveSwitch();
	};
}