/*!
@file CharaSelectUILetter.cpp
@brief �L�����N�^�[�Z���N�g��ʂ̕���UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float highSize) {
		m_textureKey = textureKey;	// �e�N�X�`��
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// �e�N�X�`�����W��UV���`
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};

		if (sideSize == NULL) m_sideSize = m_oneSize;
		else m_sideSize = sideSize;	// ����

		if (m_highSize == NULL) m_highSize = m_oneSize;
		else m_highSize = highSize;	// �c��

		m_fSidSize = size.x;		// �g�p����摜�̉����S��
		m_fHigSize = -size.y;		// �g�p����摜�̏c���S��

		m_sideSize = m_fSidSize / m_sideSize;
		m_highSize = m_fHigSize / m_highSize;

		Col4 color(1.0f);

		vector<VertexPositionColorTexture> vertices = {
			{Vec3(m_zeroSize, m_zeroSize, m_zeroSize), color, Vec2(m_zeroSize, m_zeroSize)},
			{Vec3(m_sideSize, m_zeroSize, m_zeroSize), color, Vec2(m_oneSize,  m_zeroSize)},
			{Vec3(m_zeroSize, m_highSize, m_zeroSize), color, Vec2(m_zeroSize,  m_oneSize)},
			{Vec3(m_sideSize, m_highSize, m_zeroSize), color, Vec2(m_oneSize,  m_oneSize)}
		};

		vector<uint16_t> indeces = {
			0,1,2,
			1,3,2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indeces);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);

		SetAlphaActive(true);
	}

	void BaseSprite::SettingScale(float sizes) {
		m_scale = sizes;
		auto ptrTrans = GetComponent<Transform>();
		auto spriteSize = m_scale * m_tqatSize;
		Vec3 scl(spriteSize, spriteSize, m_oneSize);
		ptrTrans->SetScale(scl);
	}

	// �|�W�V�������Z���^�[�ɍ��킹��
	void BaseSprite::SettingPositionSenter(Vec3 position) {
		auto ptrTrans = GetComponent<Transform>();
		auto xSntrPos = m_sideSize * m_helfSize * m_tqatSize;
		auto ySntrPos = m_highSize * m_helfSize * m_tqatSize;

		auto pos = ptrTrans->GetPosition();
		Vec3 senterPos(xSntrPos, ySntrPos, 0);
		ptrTrans->SetPosition((pos - senterPos * m_scale) + position);
	}

	//-----------------------------------------------------------------//

	// CharacterSelect�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CharacterStringUI::OnCreate() {
		auto texture = L"CharacterSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.9f);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �P�b�e�C(����)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void DecisionSpriteUI::OnCreate(){
		auto texture = L"Decision";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �L�����Z���Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CancelSpriteUI::OnCreate() {
		auto texture = L"Cancel";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//
	// 
	// ���h��(�߂�)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void GoToTitleSpriteUI::OnCreate() {
		auto texture = L"GoToTitle";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �X�X��(�i��)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void GoToSelectSpriteUI::OnCreate() {
		auto texture = L"GoToSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// A�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void AButtonSpriteUI::OnCreate() {
		auto texture = L"AButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// B�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void BButtonSpriteUI::OnCreate() {
		auto texture = L"BButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ReadytoFight�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void ReadyToFightUI::OnCreate() {
		auto texture = L"ReadyToFight";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// OK!!�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void OKSpriteUI::OnCreate() {
		auto texture = L"OK";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Icon
	void CharaIcon::OnCreate() {
		auto texture = L"";
		switch (m_iconNumber)
		{
		case 0:
			texture = L"LaserIcon";
			break;

		case 1:
			texture = L"TankIcon";
			break;

		default:
			texture = L"LaserIcon";
		}

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �J�[�\���X�v���C�g��\�����邽�߂̏��
	void SelectCursor::OnCreate() {
		auto texture = L"SelectCursor";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(1);
	}

	// �A�C�R���̂��ꂼ��̈ʒu�ƃA�C�R���̍ő�l
	void SelectCursor::GetIconDatas(int number,Vec3 pos) {
		m_iconPos[number] = pos;
		m_iconMaxNumber = number;
		//m_iconMaxNumber = number;

		//m_iconPos[0] = Vec3(-50.0f, 0.0f, 0.0f);
		//m_iconPos[1] = Vec3(50.0f, 0.0f, 0.0f);

		//m_iconMaxNumber = 1;
	}

	void SelectCursor::OnUpdate() {
		CursorController();
		MoveCursor();
	}

	void SelectCursor::CursorController() {
		// �X�e�B�b�N�A�����p�b�h
		const auto& ctrlVec = 
			App::GetApp()->GetInputDevice().GetControlerVec()[m_gamePadID];
		auto ctrlX = 0.0f;
		//auto ctrlY = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
			//ctrlY = ctrlVec.fThumbLY;
		}
		auto trans = GetComponent<Transform>();
		auto transPos  = trans->GetPosition();
		auto moveRight = ctrlX >=  1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		auto moveLeft  = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		//auto moveDown  = ctrlY <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		//auto moveUp	   = ctrlY >=  1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP;	

		if (!m_isSetStick) {
			m_moveTime = 0; // ������
			// �E��
			if (moveRight) {
				m_isSetStick = true;
				if (m_iconNumber < m_iconMaxNumber) {
					m_iconNumber++;
					SoundManager::GetInstance()->Play(L"CharacterSelectingSE");
					//m_nowPos = GetComponent<Transform>()->GetPosition();
				}
				else NotMoveAnimetion();
			}
			// ����
			else if(moveLeft) {
				m_isSetStick = true;
				if (m_iconNumber > 0) {
					m_iconNumber--;
					SoundManager::GetInstance()->Play(L"CharacterSelectingSE");
					//m_nowPos = GetComponent<Transform>()->GetPosition();
				}
				else NotMoveAnimetion();
			}
		}
		else if (!moveLeft && !moveRight) m_isSetStick = false;
		//MoveCursor();
		GetComponent<Transform>()->SetPosition(m_iconPos[m_iconNumber]);
	}

	void SelectCursor::CursorControl() {}

	void SelectCursor::NotMoveAnimetion() {}

	void SelectCursor::MoveCursor() {
		if (m_moveTime >= m_moveSpeed) {
			const auto& app = App::GetApp();
			const auto& delta = app->GetElapsedTime();

			m_moveTime += delta;
		}

		if (m_nowPos != m_iconPos[m_iconNumber]) {
			Vec3 easPos;
			Easing<Vec3> easing;
			easPos = easing.EaseInOut(EasingType::Quadratic, m_nowPos, m_iconPos[m_iconNumber], m_moveTime, m_moveSpeed);
			GetComponent<Transform>()->SetPosition(easPos);
		}
	}

	int SelectCursor::SetCharacterID() { return m_iconNumber; }
}