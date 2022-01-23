/*!
@file ResultSprite.cpp
@brief リザルトで使うスプライトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ResultWinOrDrowSprite::OnCreate() {
		auto texture = L"Winner";
		if (m_win)	texture = L"Winner";
		else		texture = L"Draw";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(1));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	void KillIcon::OnCreate() {
		auto texture = L"Kill";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	void DeadIcon::OnCreate() {
		auto texture = L"Dead";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}
}