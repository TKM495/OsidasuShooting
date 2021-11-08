/*!
@file   BombPredictionLine.h
@brief  ���e�̗\�����v�Z�N���X
*/

#pragma once
#include "stdafx.h"
#include "LinePoint.h"

namespace basecross {
	class BombPredictionLine {
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
		// �\�����̌v�Z
		vector<Vec3> Calculate(const Vec3& startPoint, const Vec3& endPoint);
		// �I�u�W�F�N�g�̐���
		void CreateBox();
	public:
		BombPredictionLine(
			const shared_ptr<Stage>& stage,
			int pointCount,
			float flightTime,
			float gravity = -9.8f)
			:stages(stage), m_pointCount(pointCount),
			m_flightTime(flightTime), m_gravity(gravity)
		{
			for (int i = 0; i < m_pointCount + 1; i++)
				CreateBox();
			SetActive(false);
		}
		void Update(const Vec3& startPoint, const Vec3& endPoint);

		void SetActive(bool flg);
	};
}
