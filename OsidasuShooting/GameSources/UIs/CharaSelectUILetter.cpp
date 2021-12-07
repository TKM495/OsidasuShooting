/*!
@file CharaSelectUILetter.cpp
@brief �L�����N�^�[�Z���N�g��ʂ̕���UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float fSidSize, float highSize, float fHigSize) {
		m_textureKey = textureKey;	// �e�N�X�`��
		m_sideSize = sideSize;		// ����
		m_highSize = highSize;		// �c��

		m_fSidSize = fSidSize;		// �g�p����摜�̉����S��
		m_fHigSize = fHigSize;		// �g�p����摜�̏c���S��

		Col4 color = { 1.0f,1.0f,1.0f,1.0f };
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(m_zeroSize, m_zeroSize, m_zeroSize), color, Vec2(m_zeroSize, m_zeroSize)},
			{Vec3(m_sideSize, m_zeroSize, m_zeroSize), color, Vec2(m_oneSize,  m_zeroSize)},
			{Vec3(m_zeroSize, m_highSize, m_zeroSize), color, Vec2(m_zeroSize,  m_oneSize)},
			{Vec3(m_sideSize, m_highSize, m_zeroSize), color, Vec2( m_oneSize,  m_oneSize)}

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

	void BaseSprite::SettingSenter() {
		auto ptrTrans = GetComponent<Transform>();
		auto xSntrPos = m_sideSize * m_helfSize * m_tqatSize;
		auto ySntrPos = m_highSize * m_helfSize * m_tqatSize;

		auto pos = ptrTrans->GetPosition();
		Vec3 senterPos(xSntrPos, ySntrPos, 0);
		ptrTrans->SetPosition(pos - senterPos * m_scale);
	}

	//-----------------------------------------------------------------//

	// CharacterSelect�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CharacterStringUI::OnCreate(){
		auto wstring = L"CharacterSelect";
		auto sideSize = 1024.0f;
		auto highSize = -128.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.y = 320;
		ptrTrans->SetPosition(pos);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.9f);
		BaseSprite::SettingSenter();
	}

	//-----------------------------------------------------------------//

	// �P�b�e�C�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void DecisionSpriteUI::OnCreate(){
		auto wstring = L"Decision";
		auto sideSize = 512.0f;
		auto highSize = -256.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.x =  260;
		pos.y = -320;
		ptrTrans->SetPosition(pos);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.6f);
		BaseSprite::SettingSenter();
	}

	//-----------------------------------------------------------------//

	// �L�����Z���Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CancelSpriteUI::OnCreate(){
		auto wstring = L"Cancel";
		auto sideSize = 512.0f;
		auto highSize = -256.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.x = -350;
		pos.y = -320;
		ptrTrans->SetPosition(pos);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.6f);
		BaseSprite::SettingSenter();
	}

	//-----------------------------------------------------------------//

	// A�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void AButtonSpriteUI::OnCreate(){
		auto wstring = L"AButton";
		auto sideSize = 256.0f;
		auto highSize = -256.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.x =  410;
		pos.y = -320;
		ptrTrans->SetPosition(pos);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingSenter();
	}

	//-----------------------------------------------------------------//

	// B�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void BButtonSpriteUI::OnCreate() {
		auto wstring = L"BButton";
		auto sideSize = 256.0f;
		auto highSize = -256.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos.x = -170;
		pos.y = -320;
		ptrTrans->SetPosition(pos);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingSenter();
	}

	//-----------------------------------------------------------------//

	// ReadytoFight�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void ReadyToFightUI::OnCreate() {
		auto wstring = L"ReadyToFight";
		auto sideSize = 1024.0f;
		auto highSize = -128.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingSenter();
	}

	void ReadyToFightUI::OnUpdate() {
		auto& app = App::GetApp();
		const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[0];
		if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A)
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
	}

	//-----------------------------------------------------------------//

	// OK!!�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void OKSpriteUI::OnCreate() {
		auto wstring = L"OK";
		auto sideSize = 256.0f;
		auto highSize = -256.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_position);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingSenter();
	}
}