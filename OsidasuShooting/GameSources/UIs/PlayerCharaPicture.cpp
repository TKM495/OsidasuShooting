/*!
@file PlayerCharaPicture.cpp
@brief �v���C���[�L�����̃C���[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	// �L�����N�^�[�̉摜�\�����邽�߂̏��
	void PlayerCharaUI::OnCreate() {
		auto texture = L"GaugeBackGround";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(1.0f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

}