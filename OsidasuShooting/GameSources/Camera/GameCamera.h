/*!
@file GameCamera.h
@brief メインカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameCamera :public Camera {
		Vec3 m_defaultLocalEye;
		Vec3 m_defaultAt;
	public:
		GameCamera() :Camera() {}

		void OnCreate() override;
		void OnUpdate() override;
	};
}

//end basecross
