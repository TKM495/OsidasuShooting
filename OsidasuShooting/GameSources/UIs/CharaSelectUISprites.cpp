/*!
@file CharaSelectUISprites.cpp
@brief �L�����N�^�[�Z���N�g��UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void CharacterIcon::OnCreate() {
		//texture 256 x 256
		float sideSize = 256.0f; //fullSideSize�A�S�̂̉��̒���
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

		// �ʒu�A�g��k��
		auto ptrTrans = GetComponent<Transform>();
		Vec3 scl(oneSize * tqatSize, oneSize * tqatSize, oneSize);
		ptrTrans->SetScale(scl);
	}

	void CharacterIcon::CharacterSelecting() {

		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto ctrlX = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
		}

		auto trans = GetComponent<Transform>();
		auto transPos = trans->GetPosition();
		auto moveLeft = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		auto moveRight = ctrlX >= 1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		if (!m_isSetStick) {
			// ����
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
			// �E��
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

		//Debug::GetInstance()->Log(m_characterId);
	}

	void CharacterIcon::OnUpdate() {
		CharacterSelecting();

		//auto ptrTrans = GetComponent<Transform>();
		//auto pos = ptrTrans->GetPosition();
		//if (pos.x >= pos.x + m_movePos ||
		//	pos.x <= pos.x - m_movePos) {
		//	SetDrawActive(true);
		//}
		//else {
		//	SetDrawActive(false);
		//}
	}
}