/*!
@file CharaSelectUISprites.cpp
@brief キャラクターセレクト画面のUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	// 板ポリを作る
	void CharacterIcon::CreateSprite() {
		//texture 256 x 256
		float sideSize = 256.0f; //fullSideSize、全体の横の長さ
		float highSize = -256.0f;
		float zeroSize = 0.0f;
		float  oneSize = 1.0f;
		float quatSize = 0.25f;
		float helfSize = 0.5f;
		float tqatSize = 0.75f;

		Col4 col = { 1.0f,1.0f,1.0f,1.0f };
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(zeroSize, zeroSize, zeroSize),col,Vec2(zeroSize,zeroSize)},
			{Vec3(sideSize, zeroSize, zeroSize),col,Vec2(oneSize,zeroSize)},
			{Vec3(zeroSize, highSize, zeroSize),col,Vec2(zeroSize, oneSize)},
			{Vec3(sideSize, highSize, zeroSize),col,Vec2(oneSize, oneSize)}
		};

		vector<uint16_t> indeces = {
			0,1,2,
			1,3,2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indeces);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);

		SetAlphaActive(true);

		// 位置、拡大縮小
		auto ptrTrans = GetComponent<Transform>();
		auto iconSize = oneSize * tqatSize;
		Vec3 scl(iconSize, iconSize, oneSize);
		ptrTrans->SetScale(scl);
	}

	void CharacterIcon::OnCreate() {
		CreateSprite();
	}

	// スティック、方向パッドでアイコンが変わるようにする
	void CharacterIcon::CharacterSelecting() {
		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[m_gamePadID];
		auto ctrlX = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
		}

		auto trans = GetComponent<Transform>();
		auto transPos = trans->GetPosition();
		auto moveLeft = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		auto moveRight = ctrlX >= 1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		if (!m_isSetStick) {
			// 左へ
			if (moveLeft) {
				if (m_characterId == 0) {
					transPos.x -= m_movePos * m_enumLength;
					m_characterId = m_enumLength;
				}
				else {
					transPos.x += m_movePos;
					m_characterId -= 1;
				}
				m_isSetStick = true;
			}
			// 右へ
			else if (moveRight) {
				if (m_characterId == m_enumLength) {
					transPos.x += m_movePos * m_enumLength;
					m_characterId = 0;
				}
				else {
					transPos.x -= m_movePos;
					m_characterId += 1;
				}
				m_isSetStick = true;
			}
			trans->SetPosition(transPos);
		}
		else if (!moveLeft && !moveRight) {
			m_isSetStick = false;
		}
	}

	// 表示するアイコン
	void CharacterIcon::IconsDraw() {
		auto ptrTrans = GetComponent<Transform>();
		auto iconPos = ptrTrans->GetPosition();
		auto rot = ptrTrans->GetScale();
		auto iconSenterPos = -128;

		auto pp1 = -394.0f;
		auto pp2 = 206.0f;

		auto draw1 = iconPos.x == pp1;
		auto draw2 = iconPos.x == pp2;

		if (draw1 || draw2) {
			SetDrawActive(true);
		}
		else {
			SetDrawActive(false);
		}
	}

	void CharacterIcon::SelectedCharacter() {
		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[m_gamePadID];
		auto gamePadID = m_gamePadID + 1;

		if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
			switch (m_characterId)
			{
			case 0:
				StageManager::GetInstance()->SetPlayerType(gamePadID, PlayerType::Laser);
				break;

			case 1:
				StageManager::GetInstance()->SetPlayerType(gamePadID, PlayerType::Missile);
				break;

			default:
				break;
			}
		}
	}

	void CharacterIcon::OnUpdate() {
		CharacterSelecting();
		IconsDraw();
	}

	void SelectTriangle::OnCreate() {
		CharacterIcon::CreateSprite();
	}

	void SelectTriangle::OnUpdate() {
		if (!m_setDefPos) {
			m_defPos = GetComponent<Transform>()->GetPosition().x;
			m_setDefPos = true;
		}

		if (m_isInversion)
		{
			auto ptrTrans = GetComponent<Transform>();
		}
		CharacterSelecting();
	}

	void SelectTriangle::CharacterSelecting() {
		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[m_gamePadID];
		auto ctrlX = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
		}

		auto trans = GetComponent<Transform>();
		auto transPos = trans->GetPosition();
		auto moveLeft = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		auto moveRight = ctrlX >= 1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		if (!m_isSetStick) {
			// 左へ
			if (!m_isInversion && moveLeft) {
				auto move = m_defPos - m_movePos;
				transPos.x = move;
				m_isSetStick = true;
				SoundManager::GetInstance()->Play(L"CharacterSelectingSE");
			}
			// 右へ
			else if (m_isInversion && moveRight) {
				auto move = m_defPos + m_movePos;
				transPos.x = move;
				m_isSetStick = true;
				SoundManager::GetInstance()->Play(L"CharacterSelectingSE");
			}
		}
		else if (!moveLeft && !moveRight) {
			m_isSetStick = false;
		}

		if (transPos.x != m_defPos)
		{
			if (!m_isInversion) {
				transPos.x += 1;
				if (m_defPos <= transPos.x) {
					transPos.x = m_defPos;
				}
			}
			else {
				if (m_defPos >= transPos.x) {
					transPos.x = m_defPos;
				}
				transPos.x -= 1;
			}
		}
		trans->SetPosition(transPos);
	}
}