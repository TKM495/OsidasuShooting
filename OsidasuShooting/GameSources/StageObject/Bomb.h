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

		// 爆弾の最小半径（減衰なしの威力範囲）
		float m_minimumRadius;
		// 爆弾の最大半径（最大威力範囲）
		float m_maxRadius;

		// 爆弾の威力
		float m_power;

		// 爆発したか（1つの爆弾が多段ヒットするのを防ぐフラグ）
		bool m_isExploded;

		// オーナー
		weak_ptr<PlayerBase> m_owner;
		float PowerCalc(float distance);
	public:
		Bomb(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const PredictionLine& predictionLine,
			const Vec3& startPoint,
			const Vec3& endPoint,
			float power);

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};
}
