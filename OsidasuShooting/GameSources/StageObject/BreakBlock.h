/*!
@file   BreakBlock.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class BreakBlock : public AdvancedGameObject {
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
			const TransformData transformData/*,
			const float hp,
			const float wakeupTime*/
		) :
			AdvancedGameObject(stage),

			// �X�e�[�^�X
			m_hp(3),
			m_nowHp(0),
			m_wakeupTime(5),
			m_nowTime(0),

			// ���̑�����
			m_setPosition(0)
		{
			m_transformData = transformData;
		}

		BreakBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) {};

		//void SetUpAnimation();
		void BlockDamage(float damage);
	};
}