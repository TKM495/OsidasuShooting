/*!
@file CharaSelectUILetter.cpp
@brief キャラクターセレクト画面の文字UIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float highSize) {
		m_textureKey = textureKey;	// テクスチャ
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// テクスチャ座標でUVを定義
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};

		if (sideSize == NULL) m_sideSize = m_oneSize;
		else m_sideSize = sideSize;	// 横幅

		if (m_highSize == NULL) m_highSize = m_oneSize;
		else m_highSize = highSize;	// 縦幅

		m_fSidSize = size.x;		// 使用する画像の横幅全体
		m_fHigSize = -size.y;		// 使用する画像の縦幅全体

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

	// CharacterSelectと書かれたスプライトを表示するための情報
	void CharacterStringUI::OnCreate() {
		auto texture = L"CharacterSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.9f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ケッテイ(決定)と書かれたスプライトを表示するための情報
	void DecisionSpriteUI::OnCreate(){
		auto texture = L"Decision";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// キャンセルと書かれたスプライトを表示するための情報
	void CancelSpriteUI::OnCreate() {
		auto texture = L"Cancel";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//
	// 
	// モドル(戻る)と書かれたスプライトを表示するための情報
	void GoToTitleSpriteUI::OnCreate() {
		auto texture = L"GoToTitle";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ススム(進む)と書かれたスプライトを表示するための情報
	void GoToSelectSpriteUI::OnCreate() {
		auto texture = L"GoToSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.5);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Aと書かれたスプライトを表示するための情報
	void AButtonSpriteUI::OnCreate() {
		auto texture = L"AButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Bと書かれたスプライトを表示するための情報
	void BButtonSpriteUI::OnCreate() {
		auto texture = L"BButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ReadytoFightと書かれたスプライトを表示するための情報
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

	// OK!!と書かれたスプライトを表示するための情報
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