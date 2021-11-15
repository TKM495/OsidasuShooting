/*!
@file   BaseMenu.cpp
@brief  メニューの基底クラス実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BaseMenu::SetUpMenu() {
		// -1なのは配列に合わせるため
		m_menuNum = (int)m_menuElement.size() - 1;

		auto& stage = GetStage();
		for (auto& element : m_menuElement) {
			// 文字スプライトの生成
			auto str = stage->AddGameObject<StringSprite2>(element.name,
				Align::Horizontal::Center, Align::Vertical::Center,
				Col4(1.0f));
			// 各種パラメータのセット
			str->SetPos(element.pos);
			str->SetSize(0.9f);
			str->SetDrawLayer(m_drawLayer + 1);
			// オブジェクトを配列に格納
			m_stringSprite.push_back(str);

			// カーソルの移動方向に応じたボタンフレームを設定
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
			// フレームの生成と設定
			//auto frame = stage->AddGameObject<illusionFrame>(texName);
			//frame->SetPosition(element.pos);
			//frame->SetDrawLayer(m_drawLayer);
			//m_illusionFrame.push_back(frame);
		}
	}

	void BaseMenu::OnUpdate() {
		// 非アクティブ時は何もしない
		if (!m_bActive) {
			return;
		}

		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//コントローラの取得
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];
		bool positive = false;	//+方向
		bool negative = false;	//-方向
		// ボタンが押されたかの判定
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

		// 対応するボタンが押された場合その方向に移動しSEを鳴らす
		if (negative) {
			m_nowMenuNum--;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}
		if (positive) {
			m_nowMenuNum++;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}

		// 配列のインデックス内に収める
		if (m_nowMenuNum < 0) {
			m_nowMenuNum = m_menuNum;
		}
		if (m_nowMenuNum > m_menuNum) {
			m_nowMenuNum = 0;
		}

		// 現在選択しているボタンの点滅用
		auto time = sinf(m_delta);
		auto alpha = Lerp::CalculateLerp(0.5f, 1.0f, -1.0f, 1.0f, time, Lerp::rate::Linear);

		// 遷移中でない場合
		if (!m_bChange) {
			// 状態に応じた処理を行う
			for (int i = 0; i < m_menuElement.size(); i++) {
				// 選択されている場合
				if (i == m_nowMenuNum) {
					// フレームの状態を変更し、点滅
					//m_illusionFrame[i]->SetFrameState(illusionFrame::Status::Active);
					m_activeCol.w = alpha;
					m_stringSprite[i]->SetColor(m_activeCol);
				}
				// 選択されていない場合
				else {
					//m_illusionFrame[i]->SetFrameState(illusionFrame::Status::Invalid);
					m_stringSprite[i]->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}

		auto element = m_menuElement[m_nowMenuNum];
		// 非遷移時にボタンが押されたら
		if (pad.wPressedButtons & XINPUT_GAMEPAD_A && !m_bChange) {
			OnPushButton(element);
			PlayDecisionSE(element.sendMsg);
		}

		if (m_bChange) {
			// 遷移開始してから指定の時間が立った場合
			if (m_delayDelta > m_delayTime) {
				// リセットをしてイベントを送る
				BeforeReset();
				Reset();
				SendEvent(element.sendMsg);
			}
			m_delayDelta += delta;
		}

		// ボタン点滅の処理
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
		// メッセージを送る
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