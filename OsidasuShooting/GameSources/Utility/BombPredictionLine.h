/*!
@file   BombPredictionLine.h
@brief  爆弾の予測線計算クラス
*/

#pragma once
#include "stdafx.h"
#include "LinePoint.h"

namespace basecross {
	class BombPredictionLine {
		// 重力
		float m_gravity;
		// 点の数
		int m_pointCount;
		// 滞空時間
		float m_flightTime;
		// 予測線表示のためのオブジェクト
		vector<shared_ptr<LinePoint>> m_linePoints;
		// ステージへのポインタ
		const shared_ptr<Stage>& stages;
		// 予測線の計算
		vector<Vec3> Calculate(const Vec3& startPoint, const Vec3& endPoint);
		// オブジェクトの生成
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
