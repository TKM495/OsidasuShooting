/*!
@file   PredictionLine.cpp
@brief  予測線計算クラスの実体
*/

#include "stdafx.h"
#include "Project.h"
#include "LinePoint.h"

namespace basecross {
	PredictionLine::PredictionLine(
		const shared_ptr<Stage>& stage,
		int pointCount,
		float flightTime,
		float gravity)
		:stages(stage), m_pointCount(pointCount),
		m_flightTime(flightTime), m_gravity(gravity),
		m_type(Type::Bullet)
	{
		for (int i = 0; i < m_pointCount + 1; i++)
			CreateLinePoint();
		m_impactPoint =
			stage->AddGameObject<BoardPoly>(
				L"ImpactPoint",
				TransformData(Vec3(0), Vec3(2.0f)));
	}

	vector<Vec3> PredictionLine::BulletCalculate(const Vec3& startPoint, const Vec3& endPoint) {
		vector<Vec3> points;
		// 方向を計算
		auto direction = endPoint - startPoint;
		// directionの長さとlinePoint一つ当たりの長さを計算
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

		// 放物運動
		for (float t = 0.0f; t < m_flightTime; t += (m_flightTime / (float)m_pointCount))
		{
			points.push_back(ParabolaCalculate(startPoint, endPoint, t));
		}
		// 終点座標へ補正
		points.push_back(endPoint);
		m_impactPoint->GetTransform()->SetPosition(endPoint);
		return points;
	}

	Vec3 PredictionLine::ParabolaCalculate(const Vec3& startPoint, const Vec3& endPoint, float time) {
		// 始点と終点のy成分の差分
		auto diffY = (endPoint - startPoint).y;
		// 鉛直方向の初速度vn
		auto vn = (diffY - m_gravity * 0.5f * m_flightTime * m_flightTime) / m_flightTime;

		// 水平方向の座標を求める (x,z座標)
		// Easingクラスを使用し(time / m_flightTime)が1以上のときも計算する
		Easing<Vec3> horizontal;
		auto _endPoint = endPoint;
		auto p = horizontal.Linear(startPoint, _endPoint, time / m_flightTime, 1.0f);
		// 鉛直方向の座標 y
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
		m_impactPoint->SetDrawActive(type == Type::Bomb);

		auto direction = endPoint - startPoint;
		direction.normalize();
		auto rad = atan2f(-direction.z, direction.x) + XM_PIDIV2;
		auto IPRot = m_impactPoint->GetTransform()->GetRotation();
		Vec3 rot(0.0f, rad, 0.0f);
		m_impactPoint->GetTransform()->SetRotation(rot);

		for (int i = 0; i < points.size(); i++) {
			m_linePoints[i]->GetTransform()->SetPosition(points[i]);
			m_linePoints[i]->GetTransform()->SetRotation(rot);
		}
		SetActive(direction != Vec3(0));
	}

	void PredictionLine::SetColor(const Col4& color) {
		for (auto point : m_linePoints) {
			point->SetColor(color);
		}
	}

	void PredictionLine::SetActive(bool flg) {
		for (auto point : m_linePoints) {
			point->SetDrawActive(flg);
		}
	}
}