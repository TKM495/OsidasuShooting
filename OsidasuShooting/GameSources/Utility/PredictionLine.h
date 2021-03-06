/*!
@file   PredictionLine.h
@brief  予測線計算クラス
*/

#pragma once
#include "stdafx.h"
#include "LinePoint.h"
#include "UIs/SimpleSprite.h"

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
		// 爆弾の着弾地点スプライト
		shared_ptr<BoardPoly> m_impactPoint;
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
			float gravity = -9.8f);

		/**
		 * @brief 予測線の更新
		 *
		 * @param startPoint 開始点
		 * @param endPoint 終了点
		 * @param type タイプ
		 */
		void Update(const Vec3& startPoint, const Vec3& endPoint, Type type);

		/**
		 * @brief 放物線の計算
		 *
		 * @param startPoint 開始点
		 * @param endPoint 終了点
		 * @param time m_flightTimeを最大とした時間
		 * @return timeの時の位置
		 */
		Vec3 ParabolaCalculate(const Vec3& startPoint, const Vec3& endPoint, float time);

		/**
		 * @brief 色の設定
		 *
		 * @param color 色
		 */
		void SetColor(const Col4& color);

		/**
		 * @brief 有効無効を設定
		 *
		 * @param flg true:有効
		 */
		void SetActive(bool flg);
	};
}
