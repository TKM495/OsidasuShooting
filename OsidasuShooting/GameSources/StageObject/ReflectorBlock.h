/*!
@file   ReflectorBlock.h
@brief	���t���N�^�[�u���b�N�N���X
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class ReflectorBlock : public AdvancedGameObject {
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
		ReflectorBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData
		) :
			AdvancedGameObject(stage),
			// �N����
			m_isSetUp(false),
			m_setReflectSpin(0),

			// ���̑�����
			m_setPosition(0),
			m_isReflect(false)
		{
			m_transformData = transformData;
		}

		ReflectorBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();
	};
}