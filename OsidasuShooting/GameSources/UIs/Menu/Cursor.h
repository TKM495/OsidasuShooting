/*!
@file   Cursor.h
@brief  メニューカーソルクラス
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	class Cursor :public GameObject {
		// 色
		Col4 m_color;
		// 最大透過率
		float m_max;
		// 最小透過率
		float m_min;
		// 速度
		float m_rate;
		// 時間計測用
		float m_delta;
		// カーソルテクスチャ
		wstring m_name;
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージ
		 * @param name カーソルのテクスチャの名前
		 */
		Cursor(const shared_ptr<Stage>& stage,
			const wstring& name)
			:GameObject(stage),
			m_name(name),m_max(0.3f), m_min(0.2f), m_rate(6.0f), m_delta(0.0f)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		/**
		 * @brief 透過率の設定
		 *
		 * @param max 最大透過率
		 * @param min 最小透過率
		 */
		void SetValue(float max, float min) {
			m_max = max;
			m_min = min;
		}

		/**
		 * @brief 点滅のレートの設定
		 *
		 * @param rate レート
		 */
		void SetRate(float rate) {
			m_rate = rate;
		}
	};

}
//end basecross
