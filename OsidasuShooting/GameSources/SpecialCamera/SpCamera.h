/*!
@file SpecialCamera.h
@brief 必殺技を使ったときのカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	// 必殺技の演出用カメラ
	class SpecialCamera : public GameObject {
		// 演出用
		Vec3 m_cameraPos[2]; // 共通
		Vec3 m_lPos; // レーザーの演出

		Vec3 m_startPos;
		Vec3 m_startRot;

		// ターゲットのキャラクタ情報
		enum m_playCharacters
		{
			laser
		};

		// 演出のイージング用
		float m_move;
		float m_totalTime;
		float m_easingTime;

		// ターゲットの情報取得
		Vec3 m_playerPos;
		Vec3 m_playerRot;

	public:
		SpecialCamera(const shared_ptr<Stage>& stage);
		virtual ~SpecialCamera() {};

		virtual void PlayerTrans();
		virtual void LookAtTarget();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};



}