/*!
@file   PredictionLine.cpp
@brief  �\�����v�Z�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "LinePoint.h"

namespace basecross {
	vector<Vec3> PredictionLine::BulletCalculate(const Vec3& startPoint, const Vec3& endPoint) {
		vector<Vec3> points;
		// �������v�Z
		auto direction = endPoint - startPoint;
		// direction�̒�����linePoint�������̒������v�Z
		auto length = direction.length();
		float oneLength = length / (float)m_pointCount;

		for (int i = 0; i < m_linePoints.size(); i++) {
			Vec3 p = startPoint;
			p += Utility::ChangeVectorLength(direction, oneLength * i);
			points.push_back(p);
		}
		return points;
	}
	vector<Vec3> PredictionLine::BombCalculate(const Vec3& startPoint, const Vec3& endPoint) {
		vector<Vec3> points;

		// �����^��
		for (float t = 0.0f; t < m_flightTime; t += (m_flightTime / (float)m_pointCount))
		{
			points.push_back(ParabolaCalculate(startPoint, endPoint, t));
		}
		// �I�_���W�֕␳
		points.push_back(endPoint);
		return points;
	}

	Vec3 PredictionLine::ParabolaCalculate(const Vec3& startPoint, const Vec3& endPoint, float time) {
		// �n�_�ƏI�_��y�����̍���
		auto diffY = (endPoint - startPoint).y;
		// ���������̏����xvn
		auto vn = (diffY - m_gravity * 0.5f * m_flightTime * m_flightTime) / m_flightTime;

		// ���������̍��W�����߂� (x,z���W)
		auto p = Lerp::CalculateLerp(startPoint, endPoint, 0.0f, 1.0f, time / m_flightTime, Lerp::rate::Linear);
		// ���������̍��W y
		p.y = startPoint.y + vn * time + 0.5f * m_gravity * time * time;
		return p;
	}

	void PredictionLine::CreateLinePoint() {
		auto linePoint = stages->AddGameObject<LinePoint>(TransformData(Vec3(0.0f), Vec3(0.25f), Vec3(0.0f)));
		m_linePoints.push_back(linePoint);
	}

	void PredictionLine::Update(const Vec3& startPoint, const Vec3& endPoint, Type type) {
		vector<Vec3> points;
		switch (type)
		{
		case Type::Bullet:
			points = BulletCalculate(startPoint, endPoint);
			break;
		case Type::Bomb:
			points = BombCalculate(startPoint, endPoint);
			break;
		}

		for (int i = 0; i < points.size(); i++) {
			m_linePoints[i]->GetTransform()->SetPosition(points[i]);
			auto direction = endPoint - startPoint;
			direction.normalize();
			auto rad = atan2f(-direction.z, direction.x) + XM_PIDIV2;
			Vec3 rot(0.0f, rad, 0.0f);
			m_linePoints[i]->GetTransform()->SetRotation(rot);
			m_linePoints[i]->SetDrawActive(direction != Vec3(0));
		}
	}

	void PredictionLine::SetColor(const Col4& color) {
		for (auto point : m_linePoints) {
			point->SetColor(color);
		}
	}
}