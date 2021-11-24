/*!
@file   BaseMenu.cpp
@brief  ���j���[�̊��N���X����
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BaseMenu::SetUpMenu() {
		// -1�Ȃ͔̂z��ɍ��킹�邽��
		m_menuNum = (int)m_menuElement.size() - 1;

		auto& stage = GetStage();
		for (auto& element : m_menuElement) {
			// �����X�v���C�g�̐���
			auto str = stage->AddGameObject<StringSprite2>(element.name,
				Align::Horizontal::Center, Align::Vertical::Center,
				Col4(1.0f));
			// �e��p�����[�^�̃Z�b�g
			str->SetPos(element.pos);
			str->SetSize(0.9f);
			str->SetDrawLayer(m_drawLayer + 1);
			// �I�u�W�F�N�g��z��Ɋi�[
			m_stringSprite.push_back(str);

			// �J�[�\���̈ړ������ɉ������{�^���t���[����ݒ�
			wstring texName = L"";
			switch (m_dir)
			{
			case MenuDirection::Vertical:
				texName = L"ButtonFrame";
				break;
			case MenuDirection::Horizontal:
				texName = L"ButtonFrame2";
				break;
			}
			// �t���[���̐����Ɛݒ�
			//auto frame = stage->AddGameObject<illusionFrame>(texName);
			//frame->SetPosition(element.pos);
			//frame->SetDrawLayer(m_drawLayer);
			//m_illusionFrame.push_back(frame);
		}
	}

	void BaseMenu::OnUpdate() {
		// ��A�N�e�B�u���͉������Ȃ�
		if (!m_bActive) {
			return;
		}

		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//�R���g���[���̎擾
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];
		bool positive = false;	//+����
		bool negative = false;	//-����
		// �{�^���������ꂽ���̔���
		switch (m_dir)
		{
		case MenuDirection::Vertical:
			positive = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN;
			negative = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP;
			break;
		case MenuDirection::Horizontal:
			positive = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
			negative = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		}

		// �Ή�����{�^���������ꂽ�ꍇ���̕����Ɉړ���SE��炷
		if (negative) {
			m_nowMenuNum--;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}
		if (positive) {
			m_nowMenuNum++;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}

		// �z��̃C���f�b�N�X���Ɏ��߂�
		if (m_nowMenuNum < 0) {
			m_nowMenuNum = m_menuNum;
		}
		if (m_nowMenuNum > m_menuNum) {
			m_nowMenuNum = 0;
		}

		// ���ݑI�����Ă���{�^���̓_�ŗp
		auto time = sinf(m_delta);
		auto alpha = Lerp::CalculateLerp(0.5f, 1.0f, -1.0f, 1.0f, time, Lerp::rate::Linear);

		// �J�ڒ��łȂ��ꍇ
		if (!m_bChange) {
			// ��Ԃɉ������������s��
			for (int i = 0; i < m_menuElement.size(); i++) {
				// �I������Ă���ꍇ
				if (i == m_nowMenuNum) {
					// �t���[���̏�Ԃ�ύX���A�_��
					//m_illusionFrame[i]->SetFrameState(illusionFrame::Status::Active);
					m_activeCol.w = alpha;
					m_stringSprite[i]->SetColor(m_activeCol);
				}
				// �I������Ă��Ȃ��ꍇ
				else {
					//m_illusionFrame[i]->SetFrameState(illusionFrame::Status::Invalid);
					m_stringSprite[i]->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}

		auto element = m_menuElement[m_nowMenuNum];
		// ��J�ڎ��Ƀ{�^���������ꂽ��
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A && !m_bChange) {
			OnPushButton(element);
			PlayDecisionSE(element.sendMsg);
		}

		if (m_bChange) {
			// �J�ڊJ�n���Ă���w��̎��Ԃ��������ꍇ
			if (m_delayDelta > m_delayTime) {
				// ���Z�b�g�����ăC�x���g�𑗂�
				BeforeReset();
				Reset();
				SendEvent(element.sendMsg);
			}
			m_delayDelta += delta;
		}

		// �{�^���_�ł̏���
		m_delta += delta * m_rate;
		if (m_delta >= XM_2PI) {
			m_delta = 0.0f;
		}
	}

	void BaseMenu::OnPushButton() {
		m_bChange = true;
	}

	void BaseMenu::OnPushButton(wstring mes) {
		OnPushButton();
	}
	void BaseMenu::OnPushButton(MenuElement element) {
		OnPushButton(element.sendMsg);
	}

	void BaseMenu::PlayDecisionSE() {
		m_audio->Start(L"DecisionSE", 0, 0.1f);
	}
	void BaseMenu::PlayDecisionSE(wstring mes) {
		PlayDecisionSE();
	}

	void BaseMenu::SendEvent(wstring mes) {
		// ���b�Z�[�W�𑗂�
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), mes);
	}

	void BaseMenu::Reset() {
		m_bChange = false;
		m_delayDelta = 0.0f;
		m_nowMenuNum = 0;
	}

	void BaseMenu::SetDrawMenu(bool flg) {
		for (auto& string : m_stringSprite) {
			string->SetDrawActive(flg);
		}
		//for (auto& frame : m_illusionFrame) {
		//	frame->SetDrawActive(flg);
		//}
		m_bActive = flg;
	}

	void BaseMenu::ResetDrawLayer(int layer) {
		for (auto& string : m_stringSprite) {
			string->SetDrawLayer(layer + 1);
		}
		//for (auto& frame : m_illusionFrame) {
		//	frame->SetDrawLayer(layer);
		//}
	}
}
//end basecross