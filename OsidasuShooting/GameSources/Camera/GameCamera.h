/*!
@file GameCamera.h
@brief ゲームカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameCamera :public Camera {
		/**
		 * @brief ステート
		 */
		enum class State {
			Init,	// 初期化
			Update,	// 更新
		};
		// Atを基準にしたEyeの位置
		Vec3 m_defaultLocalEye;
		// 初期のAtの位置
		Vec3 m_defaultAt;
		// 追従速度
		float m_followUpVelocity;
		// 最小ズーム
		float m_minZoom;
		// 最大ズーム
		float m_maxZoom;
		// ズーム値の範囲
		float m_zoomLimiter;
		// 最小Y座標
		float m_minimumY;
		// 現在のステート
		State m_state;
		// 移動できる範囲
		Vec2 m_area;
		// 初期化処理
		void Init();
		// 更新処理
		void Update();
		/**
		 * @brief AtとEyeを設定
		 *
		 * @param at Atの位置
		 */
		void SetAtAndEye(const Vec3& at);
		/**
		 * @brief ズームのセット
		 *
		 * @param level 視野角(rad)
		 */
		void SetZoomLevel(float level);
		/**
		 * @brief 各プレイヤーが入るAABBを取得
		 *
		 * @return 各プレイヤーが入るAABB
		 */
		AABB GetAABB();
		/**
		 * @brief 中心点を取得
		 *
		 * @return 各プレイヤーの中心点
		 */
		Vec3 GetCenterPoint();
		/**
		 * @brief 各プレイヤーの最大距離を取得
		 *
		 * @return 各プレイヤーの最大距離
		 */
		float GetGreatestDistance();
	public:
		GameCamera();

		void OnCreate() override;
		void OnUpdate() override;

		void SetArea(const Vec2& area) {
			m_area = area;
		}
	};
}

//end basecross
