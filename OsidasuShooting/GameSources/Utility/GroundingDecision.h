/*!
@file   GroundingDecision.h
@brief  接地判定クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GroundingDecision {
		// オブジェクトの半径
		float m_radius;
		// しきい値
		static float m_threshold;
		// 初期化したか
		bool m_isInit;
	public:
		// コンストラクタ
		GroundingDecision();
		GroundingDecision(float radius);
		GroundingDecision(const Vec3& scale);

		/**
		 * @brief 判定
		 *
		 * @param pos 自身の位置
		 * @return trueなら接地している
		 */
		bool Calculate(const Vec3& pos);

		/**
		 * @brief 自身の半径の設定
		 *
		 * @param radius 半径
		 */
		void SetRadius(float radius) {
			m_radius = radius;
			m_isInit = true;
		}
		/**
		 * @brief 自身の半径の設定
		 *
		 * @param scale 自身のスケール
		 */
		void SetRadius(const Vec3& scale) {
			m_radius = scale.y / 2.0f;
			m_isInit = true;
		}
	};
}
