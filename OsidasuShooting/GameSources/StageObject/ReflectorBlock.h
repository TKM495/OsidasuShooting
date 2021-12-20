/*!
@file   Reflector.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "Block.h"

namespace basecross {

	class Reflector : public Block {
	//�N����
		// �N�������ǂ���
		bool m_isSetUp;
		// �N�����A�j���[�V����
		float m_setReflectSpin;

	// ���̑�����
		// �ݒu�ꏊ
		Vec3 m_setPosition;
		// ���˂��o���邩�ǂ���
		bool m_isReflect;

	public:
		Reflector(
			shared_ptr<Stage>& stage,
			const TransformData transformData 
		):
			Block(stage,transformData),
			// �N����
			m_isSetUp(false),
			m_setReflectSpin(0),

			// ���̑�����
			m_setPosition(0),
			m_isReflect(false)
		{
			m_transformData = transformData;
		}

		Reflector(const shared_ptr<Stage>& stage,
			const TransformData transformData,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();

	};
}