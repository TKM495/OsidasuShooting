/*!
@file   BreakBlock.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "Block.h"
#include "JonyMd/CountDown.h"

namespace basecross {
	class BreakBlock : public Block {
	//�N����
		// �N�������ǂ���
		bool m_isSetUp;

	// �X�e�[�^�X
		// �u���b�N��HP
		float m_hp;
		float m_nowHp;

		// ��������
		float m_wakeupTime;
		float m_nowTime;
	// ���̑�����
		// �ݒu�ꏊ
		Vec3 m_setPosition;

	public:
		BreakBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData,
			const float hp,
			const float wakeupTime
		) :
			Block(stage, transformData),
			// �N����
			m_isSetUp(false),

			// �X�e�[�^�X
			m_hp(hp),
			m_nowHp(0),
			m_wakeupTime(wakeupTime),
			m_nowTime(0),

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
		void OnCollisionEnter(shared_ptr<GameObject>& other) {};

		void SetUpAnimation();
		void BlockDamage(float damage);

	};
}