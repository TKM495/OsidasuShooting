#include "stdafx.h"
#include "Project.h"
#include "DebugCamera.h"

namespace basecross {
	void DebugCamera::OnCreate() {
		auto eye = Vec3(cosf(angleRadY), 0.0f, sinf(angleRadY)) * length;
		eye += Vec3(0.0f, 15.0f, 0.0f);
		SetEye(eye);
		SetAt(0.0f, 0.0f, 0.0f);
	}

	void DebugCamera::OnUpdate() {
		auto& app = App::GetApp(); //アプリケーションオブジェクトを取得
		auto scene = app->GetScene<Scene>(); //アプリケーションオブジェクトからシーンを取得
		auto stage = scene->GetActiveStage(); //シーンからステージを取得する

		auto delta = app->GetElapsedTime();

		auto device = app->GetInputDevice();

		int i = 0;
		if (device.GetKeyState().m_bPushKeyTbl[VK_LEFT]) {
			i = -1;
		}
		if (device.GetKeyState().m_bPushKeyTbl[VK_RIGHT]) {
			i = 1;
		}

		//スティックの傾きに応じてカメラを回り込ませる
		auto deg = i * 90.0f;
		angleRadY += XMConvertToRadians(deg) * delta;

		//カメラの回り込みの角度と距離で位置を決定する
		auto eye = Vec3(cosf(angleRadY), 0.0f, sinf(angleRadY)) * length;
		eye += Vec3(0.0f, 15.0f, 0.0f);
		SetEye(eye);
	}
}