/*!
@file   Bomb.h
@brief  爆弾クラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Bomb :public StageObject {
		// PredictionLineのインスタンス
		PredictionLine m_predictionLine;
		// 開始位置
		Vec3 m_startPoint;
		// 終了位置
		Vec3 m_endPoint;
		// タイムレート
		float m_timeRate;
		// 経過時間
		float m_delta;

		// 爆弾の影響半径
		float m_radius;
		// 爆弾の威力
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
