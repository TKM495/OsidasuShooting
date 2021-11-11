/*!
@file   PredictionLine.h
@brief  �\�����v�Z�N���X
*/

#pragma once
#include "stdafx.h"
#include "LinePoint.h"

namespace basecross {
	class PredictionLine {
	public:
		// �\�����̎��
		enum class Type {
			Bullet,
			Bomb
		};
	private:
		// �\�����^�C�v
		Type m_type;
		// �d��
		float m_gravity;
		// �_�̐�
		int m_pointCount;
		// �؋󎞊�
		float m_flightTime;
		// �\�����\���̂��߂̃I�u�W�F�N�g
		vector<shared_ptr<LinePoint>> m_linePoints;
		// �X�e�[�W�ւ̃|�C���^
		const shared_ptr<Stage>& stages;
		// �e�̗\�����̌v�Z
		vector<Vec3> BulletCalculate(const Vec3& startPoint, const Vec3& endPoint);
		// ���e�̗\�����̌v�Z
		vector<Vec3> BombCalculate(const Vec3& startPoint, const Vec3& endPoint);
		// �I�u�W�F�N�g�̐���
		void CreateLinePoint();
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage	�X�e�[�W�ւ̃|�C���^
		 * @param pointCount �_�̐�
		 * @param flightTime ���e�̔��Ď���
		 * @param gravity �d�͉����x
		 */
		PredictionLine(
			const shared_ptr<Stage>& stage,
			int pointCount,
			float flightTime,
			float gravity = -9.8f)
			:stages(stage), m_pointCount(pointCount),
			m_flightTime(flightTime), m_gravity(gravity), m_type(Type::Bullet)
		{
			for (int i = 0; i < m_pointCount + 1; i++)
				CreateLinePoint();
		}

		/**
		 * @brief �\�����̍X�V
		 *
		 * @param startPoint �J�n�_
		 * @param endPoint �I���_
		 * @param type �^�C�v
		 */
		void Update(const Vec3& startPoint, const Vec3& endPoint, Type type);

		/**
		 * @brief �\�����邩�ǂ���
		 *
		 * @param flg true:�\������
		 */
		void SetActive(bool flg);
	};
}
