/*!
@file   GameController.cpp
@brief  �R���g���[���[�Ǘ��N���X�̎���
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameController::GameController(PlayerNumber number)
		:m_playerNumber(number), m_isVibrationON(false)
	{}

	GameController::~GameController() {
		// ���Z�b�g���Ȃ��ƃo�C�u���[�V�������~�܂�Ȃ�
		ResetVibration();
	}

	CONTROLER_STATE GameController::GetControler() {
		const auto& cntlPadVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		auto gameStage = dynamic_pointer_cast<GameStage>(stage);
		// 0�ȉ��̏ꍇ�����I��0�ɂ���
		auto index = (UINT)m_playerNumber < 0 ? 0 : (UINT)m_playerNumber;
		CONTROLER_STATE cntlPad = cntlPadVec[index];
		if (gameStage) {
			switch (gameStage->GetCurrentGameState())
			{
			case GameStage::GameState::PLAYING:
				break;
			default:
				// �����I�ɕύX
				cntlPad.bConnected = false;
				break;
			}
		}
		return cntlPad;
	}

	Vec3 GameController::GetLeftStickVec() {
		auto vec = GetStickVec(Direction::Left);
		return Vec3(vec.x, 0.0f, vec.y);
	}
	Vec3 GameController::GetRightStickVec() {
		auto vec = GetStickVec(Direction::Right);
		return Vec3(vec.x, 0.0f, vec.y);
	}

	Vec2 GameController::GetStickVec(Direction direction) {
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

	bool GameController::GetRightTrigger() {
		return GetTrigger(Direction::Right);
	}
	bool GameController::GetLeftTrigger() {
		return GetTrigger(Direction::Left);
	}

	bool GameController::GetTrigger(Direction direction) {
		const auto& cntlPad = GetControler();
		if (!cntlPad.bConnected)
			return false;
		switch (direction)
		{
		case Direction::Left:
			return cntlPad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		case Direction::Right:
			return cntlPad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		}

		return false;
	}

	void GameController::ActiveVibrationThread(const VibrationData& data) {
		// �o�C�u���[�V�����J�n
		XINPUT_VIBRATION vibration = { data.LeftMotorSpeed,data.RightMotorSpeed };
		XInputSetState((WORD)m_playerNumber, &vibration);

		// �w�肵���b���ҋ@
		Sleep(DWORD(data.Time * 1000));
		// ���Z�b�g�i0�ɖ߂��j
		ResetVibration();
	}

	void GameController::SetVibration(const VibrationData& data) {
		// ���łɃo�C�u���[�V������ON�ɂȂ��Ă���ꍇ�V�����X���b�h�𗧂ĂȂ�
		if (m_isVibrationON)
			return;

		m_isVibrationON = true;
		//���̃��\�[�X��ǂݍ��ރX���b�h�̃X�^�[�g
		thread vibrationThread(&GameController::ActiveVibrationThread, this, data);
		//�I���܂ł͑҂��Ȃ�
		vibrationThread.detach();
	}

	void GameController::ResetVibration() {
		m_isVibrationON = false;
		XINPUT_VIBRATION vibration = { 0,0 };
		XInputSetState((WORD)m_playerNumber, &vibration);
	}
}