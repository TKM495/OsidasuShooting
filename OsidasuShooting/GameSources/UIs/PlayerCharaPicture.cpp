/*!
@file PlayerCharaPicture.cpp
@brief プレイヤーキャラのイメージ実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	// キャラクターの画像表示するための情報
	void PlayerCharaPicture::OnCreate() {
		auto texture = L"";
		switch (m_playerNumebr)
		{
		case 0:
			break;
		case 1:
			break;
		default:
			break;
		}

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(1.0f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	void PlayerCharaPicture::OnUpdate() {

	}


}