/*!
@file   PredictionLine.h
@brief  予測線計算クラス
*/

#pragma once
#include "stdafx.h"
#include "LinePoint.h"

namespace basecross {
	class PredictionLine {
	public:
		// 予測線の種類
		enum class Type {
			Bullet,
			Bomb
		};
	private:
		// 予測線タイプ
		Type m_type;
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
		// 弾の予測線の計算
		vector<Vec3> BulletCalculate(const Vec3& startPoint, const Vec3& endPoint);
		// 爆弾の予測線の計算
		vector<Vec3> BombCalculate(const Vec3& startPoint, const Vec3& endPoint);
		// オブジェクトの生成
		void CreateLinePoint();
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage	ステージへのポインタ
		 * @param pointCount 点の数
		 * @param flightTime 爆弾の飛翔時間
		 * @param gravity 重力加速度
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
		 * @brief 予測線の更新
		 *
		 * @param startPoint 開始点
		 * @param endPoint 終了点
		 * @param type タイプ
		 */
		void Update(const Vec3& startPoint, const Vec3& endPoint, Type type);

		/**
		 * @brief 表示するかどうか
		 *
		 * @param flg true:表示する
		 */
		void SetActive(bool flg);
	};
}
