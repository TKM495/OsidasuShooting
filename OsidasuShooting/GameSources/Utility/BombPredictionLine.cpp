/*!
@file   BombPredictionLine.cpp
@brief  ���e�̗\�����v�Z�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "LinePoint.h"

namespace basecross {
	vector<Vec3> BombPredictionLine::Calculate(const Vec3& startPoint, const Vec3& endPoint) {
		vector<Vec3> points;

		auto diffY = (endPoint - startPoint).y; // �n�_�ƏI�_��y�����̍���
		auto vn = (diffY - m_gravity * 0.5f * m_flightTime * m_flightTime) / m_flightTime; // ���������̏����xvn

		// �����^��
		for (float t = 0.0f; t < m_flightTime; t += (m_flightTime / (float)m_pointCount))
		{
			// ���������̍��W�����߂� (x,z���W)
			auto p = Lerp::CalculateLerp(startPoint, endPoint, 0.0f, 1.0f, t / m_flightTime, Lerp::rate::Linear);
			p.y = startPoint.y + vn * t + 0.5f * m_gravity * t * t; // ���������̍��W y
			points.push_back(p);
		}
		// �I�_���W�֕␳
		points.push_back(endPoint);
		return points;
	}

	void BombPredictionLine::CreateBox() {
		const auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		auto linePoint = stages->AddGameObject<LinePoint>(TransformData(Vec3(0.0f), Vec3(1.0f), Vec3(0.0f)));
		m_linePoints.push_back(linePoint);
	}

	void BombPredictionLine::Update(const Vec3& startPoint, const Vec3& endPoint) {
		auto points = Calculate(startPoint, endPoint);
		for (int i = 0; i < points.size(); i++) {
			m_linePoints[i]->GetTransform()->SetPosition(points[i]);
		}
	}

	void BombPredictionLine::SetActive(bool flg) {
		for (auto linePoint : m_linePoints) {
			linePoint->SetDrawActive(flg);
		}
	}
}