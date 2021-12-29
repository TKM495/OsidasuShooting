/*!
@file   PhysicalBehavior.h
@brief  物理的な挙動を行うコンポーネントクラス
*/

#pragma once
#include "stdafx.h"
#include "Utility/GroundingDecision.h"

namespace basecross {
	class PhysicalBehavior :public Component {
		// 空気抵抗
		float m_airDrag;
		// 地面の抵抗
		float m_groundDrag;
		// 最大速度
		float m_maxSpeed;
		// 現在の速度
		Vec3 m_velocity;
		// しきい値（移動速度がこの値より小さい場合0とみなす）
		float m_threshold;
		// 接地判定クラス
		unique_ptr<GroundingDecision> m_groundingDecision;
	public:
		// コンストラクタ
		PhysicalBehavior(const shared_ptr<GameObject>& gameObjectPtr)
			:Component(gameObjectPtr),
			m_velocity(Vec3(0.0f)), m_groundDrag(3.0f), m_airDrag(1.0f),
			m_maxSpeed(200.0f), m_threshold(0.05f)
		{}

		// コンポーネントの生成
		void OnCreate()override;
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
		 * @brief 現在の速度を取得
		 *
		 * @return 現在の速度
		 */
		Vec3 GetVelocity() {
			return m_velocity;
		}

		/**
		 * @brief 速度を0にする
		 */
		void SetVelocityZero() {
			m_velocity = Vec3(0);
		}
	};
}
