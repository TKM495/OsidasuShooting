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

	void BaseSprite::SettingPosition(Vec3 position) {
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
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �P�b�e�C(����)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void DecisionSpriteUI::OnCreate(){
		auto texture = L"Decision";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �L�����Z���Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CancelSpriteUI::OnCreate() {
		auto texture = L"Cancel";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//
	// 
	// ���h��(�߂�)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void GoToTitleSpriteUI::OnCreate() {
		auto texture = L"GoToTitle";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �X�X��(�i��)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void GoToSelectSpriteUI::OnCreate() {
		auto texture = L"GoToSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// A�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void AButtonSpriteUI::OnCreate() {
		auto texture = L"AButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// B�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void BButtonSpriteUI::OnCreate() {
		auto texture = L"BButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ReadytoFight�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void ReadyToFightUI::OnCreate() {
		auto texture = L"ReadyToFight";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingPosition(m_setPos);
	}

	void ReadyToFightUI::OnUpdate() {
		//auto& app = App::GetApp();
		//const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[0];
		//if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
		//	PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
		//}
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
		BaseSprite::SettingPosition(m_setPos);
	}
}