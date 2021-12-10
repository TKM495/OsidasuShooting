/*!
@file CharaSelectUILetter.cpp
@brief キャラクターセレクト画面の文字UIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float fSidSize, float highSize, float fHigSize) {
		m_textureKey = textureKey;	// テクスチャ
		m_sideSize = sideSize;		// 横幅
		m_highSize = highSize;		// 縦幅

		m_fSidSize = fSidSize;		// 使用する画像の横幅全体
		m_fHigSize = fHigSize;		// 使用する画像の縦幅全体

		Col4 color = { 1.0f,1.0f,1.0f,1.0f };
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

	// CharacterSelectと書かれたスプライトを表示するための情報
	void CharacterStringUI::OnCreate() {
		auto wstring = L"CharacterSelect";
		auto sideSize = 1024.0f;
		auto highSize = -128.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.9f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ケッテイ(決定)と書かれたスプライトを表示するための情報
	void DecisionSpriteUI::OnCreate(){
		auto wstring = L"Decision";
		auto sideSize = 512.0f;
		auto highSize = -256.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// キャンセルと書かれたスプライトを表示するための情報
	void CancelSpriteUI::OnCreate() {
		auto wstring = L"Cancel";
		auto sideSize = 512.0f;
		auto highSize = -256.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//
	// 
	// モドル(戻る)と書かれたスプライトを表示するための情報
	void GoToTitleSpriteUI::OnCreate() {
		auto wstring = L"GoToTitle";
		auto sideSize = 512.0f;
		auto highSize = -256.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ススム(進む)と書かれたスプライトを表示するための情報
	void GoToSelectSpriteUI::OnCreate() {
		auto wstring = L"GoToSelect";
		auto sideSize = 512.0f;
		auto highSize = -256.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Aと書かれたスプライトを表示するための情報
	void AButtonSpriteUI::OnCreate() {
		auto wstring = L"AButton";
		auto sideSize = 256.0f;
		auto highSize = -256.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL); 
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Bと書かれたスプライトを表示するための情報
	void BButtonSpriteUI::OnCreate() {
		auto wstring = L"BButton";
		auto sideSize = 256.0f;
		auto highSize = -256.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ReadytoFightと書かれたスプライトを表示するための情報
	void ReadyToFightUI::OnCreate() {
		auto wstring = L"ReadyToFight";
		auto sideSize = 1024.0f;
		auto highSize = -128.0f;

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingPosition(m_setPos);
	}

	void ReadyToFightUI::OnUpdate() {
		auto& app = App::GetApp();
		const auto& ctrlVec = app->GetInputDevice().GetControlerVec()[0];
		if (ctrlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
			PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGameStage");
		}
	}

	//-----------------------------------------------------------------//

	// OK!!と書かれたスプライトを表示するための情報
	void OKSpriteUI::OnCreate() {
		auto wstring = L"OK";
		auto sideSize = 256.0f;
		auto highSize = -256.0f;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(wstring, sideSize, NULL, highSize, NULL);
		BaseSprite::SettingScale(1);
		BaseSprite::SettingPosition(m_setPos);
	}
}