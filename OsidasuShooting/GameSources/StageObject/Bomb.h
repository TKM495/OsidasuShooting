/*!
@file   Bomb.h
@brief  ���e�N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Bomb :public StageObject {
		// PredictionLine�̃C���X�^���X
		PredictionLine m_predictionLine;
		// �J�n�ʒu
		Vec3 m_startPoint;
		// �I���ʒu
		Vec3 m_endPoint;
		// �^�C�����[�g
		float m_timeRate;
		// �o�ߎ���
		float m_delta;

		// ���e�̉e�����a
		float m_radius;
		// ���e�̈З�
		float m_power;
	public:
		Bomb(const shared_ptr<Stage>& stage,
			const PredictionLine& predictionLine,
			const Vec3& startPoint,
			const Vec3& endPoint)
			:StageObject(stage), m_predictionLine(predictionLine),
			m_delta(0.0f), m_startPoint(startPoint), m_endPoint(endPoint),
			m_timeRate(2.0f), m_radius(3.0f), m_power(700.0f)
		{
			m_transformData.Position = m_startPoint;
			m_transformData.Scale = Vec3(0.5f);
		}

		void OnCreate()override;
		void OnUpdate()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};
}
