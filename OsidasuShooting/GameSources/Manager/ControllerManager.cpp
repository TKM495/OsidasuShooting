/*!
@file   ControllerManager.cpp
@brief  コントローラーマネージャーの実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ControllerManager::ControllerManager(PlayerNumber number)
		:m_playerNumber(number), m_triggerThreshold(128.0f)
	{}

	CONTROLER_STATE ControllerManager::GetControler() {
		const auto& cntlPadVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		auto gameStage = dynamic_pointer_cast<GameStage>(stage);
		// 0以下の場合強制的に0にする
		auto index = (UINT)m_playerNumber < 0 ? 0 : (UINT)m_playerNumber;
		CONTROLER_STATE cntlPad = cntlPadVec[index];
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
		auto vec = GetStickVec(Direction::Left);
		return Vec3(vec.x, 0.0f, vec.y);
	}
	Vec3 ControllerManager::GetRightStickVec() {
		auto vec = GetStickVec(Direction::Right);
		return Vec3(vec.x, 0.0f, vec.y);
	}

	Vec2 ControllerManager::GetStickVec(Direction direction) {
		const auto& cntlPad = GetControler();
		if (!cntlPad.bConnected)
			return Vec2(0.0f);

		float fThumbX = 0.0f;
		float fThumbY = 0.0f;

		switch (direction)
		{
		case Direction::Left:
			fThumbX = cntlPad.fThumbLX;
			fThumbY = cntlPad.fThumbLY;
			break;
		case Direction::Right:
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

	bool ControllerManager::GetRightTrigger() {
		return GetTrigger(Direction::Right);
	}
	bool ControllerManager::GetLeftTrigger() {
		return GetTrigger(Direction::Left);
	}

	bool ControllerManager::GetTrigger(Direction direction) {
		const auto& cntlPad = GetControler();
		if (!cntlPad.bConnected)
			return false;
		switch (direction)
		{
		case Direction::Left:
			return cntlPad.bLeftTrigger > m_triggerThreshold;
		case Direction::Right:
			return cntlPad.bRightTrigger > m_triggerThreshold;
		}

		return false;
	}
}