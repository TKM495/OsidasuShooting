/*!
@file PlayerCharaPicture.cpp
@brief �v���C���[�L�����̃C���[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	// �L�����N�^�[�̉摜�\�����邽�߂̏��
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