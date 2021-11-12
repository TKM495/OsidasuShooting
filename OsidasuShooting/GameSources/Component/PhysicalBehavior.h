/*!
@file   PhysicalBehavior.h
@brief  物理的な挙動を行うコンポーネントクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PhysicalBehavior :public Component {
		// 抵抗力
		float m_drag;
		// 現在の速度
		Vec3 m_velocity;
		// しきい値（移動速度がこの値より小さい場合0とみなす）
		float m_threshold;
	public:
		// コンストラクタ
		PhysicalBehavior(const shared_ptr<GameObject>& gameObjectPtr)
			:Component(gameObjectPtr),
			m_velocity(Vec3(0.0f)), m_drag(3.0f), m_threshold(0.05f)
		{}

		// コンポーネントの生成
		void OnCreate()override {}
		// コンポーネントの更新
		void OnUpdate()override;
		// コンポーネントの描画
		void OnDraw()override {}

		/**
		 * @brief 移動
		 *
		 * @param force かける力
		 */
		void Move(const Vec3& force);
		/**
		 * @brief 移動
		 *
		 * @param direction	方向
		 * @param force かける力
		 */
		void Move(const Vec3& direction, float force);

		/**
		 * @brief 瞬間的に力を加える
		 *
		 * @param force かける力
		 */
		void Impact(const Vec3& force);

		/**
		 * @brief 瞬間的に力を加える
		 *
		 * @param direction 方向
		 * @param force かける力
		 */
		void Impact(const Vec3& direction, float force);

		/**
		 * @brief Dragを設定
		 *
		 * @param drag 設定値
		 */
		void SetDrag(float drag) {
			m_drag = drag;
		}
		/**
		 * @brief Dragを取得
		 *
		 * @return 現在のDrag
		 */
		float GetDrag() {
			return m_drag;
		}

		/**
		 * @brief 現在の速度を取得
		 *
		 * @return 現在の速度
		 */
		float GetSpeed() {
			return m_velocity.length();
		}
	};
}
