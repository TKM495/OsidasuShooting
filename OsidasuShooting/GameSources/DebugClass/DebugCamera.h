/*!
@file DebugCamera.h
@brief メインカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class DebugCamera :public Camera {
		float angleRadY; //カメラの回り込み角度(ラジアン)
		float length; //カメラの注視点からの距離
		float height;
	public:
		DebugCamera()
			:angleRadY(XMConvertToRadians(-90)), length(30.0f), height(30.0f)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		//カメラの回り込みをラジアン角で取得する
		float GetAngleRadY() const {
			return angleRadY;
		}
	};
}

//end basecross
