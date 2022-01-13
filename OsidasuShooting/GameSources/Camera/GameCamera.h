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
		// 現在のステート
		State m_state;
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
		 * @brief 中心点を取得
		 *
		 * @return プレイヤーの中心点
		 */
		Vec3 GetCenterPoint();
	public:
		GameCamera();

		void OnCreate() override;
		void OnUpdate() override;
	};
}

//end basecross
