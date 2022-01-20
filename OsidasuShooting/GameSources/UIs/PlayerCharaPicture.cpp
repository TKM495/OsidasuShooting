/*!
@file PlayerCharaPicture.cpp
@brief プレイヤーキャラのイメージ実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	// プレイヤーのナンバー
	wstring PlayerCharaPicture::PlayerNumber() {
		wstring playerNum = L"1";

		switch (m_gamePadIDs)
		{
		case 0:
			playerNum = L"1";
			break;

		case 1:
			playerNum = L"2";
			break;

		case 2:
			playerNum = L"3";
			break;

		case 3:
			playerNum = L"4";
			break;

		default:
			break;
		}
		return playerNum;
	}
	
	// プレイヤーのキャラクター
	wstring PlayerCharaPicture::PlayerCharacter() {
		wstring playerChara = L"";
		switch (m_charaID)
		{
		case 0:
			playerChara = L"LaserPicture";
			break;

		case 1:
			playerChara = L"TankPicture";
			break;

		default:
			break;
		}

		return playerChara;
	}

	// キャラクターの画像表示するための情報
	void PlayerCharaPicture::OnCreate() {
		PlayerCharacter();
		PlayerNumber();

		auto texture = PlayerCharacter() + PlayerNumber();

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.6f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	void PlayerCharaPicture::DrawCharacter(int gamePadID) {

	}

	void PlayerCharaPicture::OnUpdate() {

	}


}