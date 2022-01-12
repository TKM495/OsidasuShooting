/*!
@file GameCamera.h
@brief メインカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameCamera :public Camera {
		enum class State {
			Init,	// 初期化
			Update,	// 更新
		};
		Vec3 m_defaultLocalEye;
		Vec3 m_defaultAt;
		Vec3 m_def;
		State m_state;
		void Init();
		void Update();
		void SetAtAndEye(const Vec3& at);
	public:
		GameCamera();

		void OnCreate() override;
		void OnUpdate() override;
	};
}

//end basecross
