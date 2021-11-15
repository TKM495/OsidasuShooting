/*!
@file   GroundingDecision.h
@brief  接地判定クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GroundingDecision {
		// オブジェクトの高さ
		float m_height;
		// しきい値
		static float m_threshold;
		// 初期化したか
		bool m_isInit;
		// 判定から除外するタグ
		vector<wstring> m_tagDoNotDecision;
	public:
		// コンストラクタ
		GroundingDecision();
		GroundingDecision(float height);
		GroundingDecision(const Vec3& scale);

		/**
		 * @brief 判定
		 *
		 * @param pos 自身の位置
		 * @return trueなら接地している
		 */
		bool Calculate(const Vec3& pos);

		/**
		 * @brief 判定に使う高さの設定
		 *
		 * @param height 高さ
		 */
		void SetRadius(float height) {
			m_height = height;
			m_isInit = true;
		}
		/**
		 * @brief 自身の半径の設定
		 *
		 * @param scale 自身のスケール
		 */
		void SetRadius(const Vec3& scale) {
			m_height = scale.y;
			m_isInit = true;
		}

		/**
		 * @brief 判定から除外するタグを追加
		 *
		 * @param tag タグ
		 */
		void AddNotDecisionTag(const wstring& tag) {
			m_tagDoNotDecision.push_back(tag);
		}
	};
}
