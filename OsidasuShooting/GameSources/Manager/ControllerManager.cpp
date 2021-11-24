/*!
@file   ControllerManager.cpp
@brief  コントローラーマネージャーの実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ControllerManager::ControllerManager(PlayerNumber number)
		:m_playerNumber(number)
	{}

	CONTROLER_STATE ControllerManager::GetControler() {
		const auto& cntlPadVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		auto gameStage = dynamic_pointer_cast<GameStage>(stage);
		CONTROLER_STATE cntlPad = cntlPadVec[(UINT)m_playerNumber];
		if (gameStage) {
			switch (gameStage->GetCurrentGameState())
			{
			case GameStage::GameState::PLAYING:
				break;
			default:
				// 強制的に変更
				cntlPad.bConnected = false;
				break;
			}
		}
		return cntlPad;
	}

	Vec3 ControllerManager::GetLeftStickVec() {
		auto vec = GetStickVec(Stick::Left);
		return Vec3(vec.x, 0.0f, vec.y);
	}
	Vec3 ControllerManager::GetRightStickVec() {
		auto vec = GetStickVec(Stick::Right);
		return Vec3(vec.x, 0.0f, vec.y);
	}

	Vec2 ControllerManager::GetStickVec(Stick stick) {
		const auto& cntlPad = GetControler();
		if (!cntlPad.bConnected)
			return Vec2(0.0f);

		float fThumbX = 0.0f;
		float fThumbY = 0.0f;

		switch (stick)
		{
		case Stick::Left:
			fThumbX = cntlPad.fThumbLX;
			fThumbY = cntlPad.fThumbLY;
			break;
		case Stick::Right:
			fThumbX = cntlPad.fThumbRX;
			fThumbY = cntlPad.fThumbRY;
			break;
		}

		Vec2 stickVec(0.0f);
		if (fThumbX != 0.0f || fThumbY != 0.0f) {
			stickVec = Vec2(fThumbX, fThumbY);
		}
		return stickVec;
	}
}