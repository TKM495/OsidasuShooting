/*!
@file   Bomb.h
@brief  爆弾クラス
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"
#include "PlayerBase.h"

namespace basecross {
	class Bomb :public AdvancedGameObject {
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
		// 生存時間
		float m_lifeSpan;

		// 爆弾の影響半径
		float m_radius;
		// 爆弾の威力
		float m_power;

		// 爆発したか（1つの爆弾が多段ヒットするのを防ぐフラグ）
		bool m_isExploded;

		// オーナー
		weak_ptr<PlayerBase> m_owner;
	public:
		Bomb(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const PredictionLine& predictionLine,
			const Vec3& startPoint,
			const Vec3& endPoint,
			float power)
			:AdvancedGameObject(stage), m_owner(owner),
			m_predictionLine(predictionLine),
			m_delta(0.0f), m_startPoint(startPoint), m_endPoint(endPoint),
			m_timeRate(2.0f), m_radius(3.0f), m_power(power), m_lifeSpan(5.0f),
			m_isExploded(false)
		{
			m_transformData.Position = m_startPoint;
			m_transformData.Scale = Vec3(0.5f);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};
}
