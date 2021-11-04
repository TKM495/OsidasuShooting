/*!
@file   Debug.cpp
@brief  デバッグクラス実体
*/

#include "stdafx.h"
#include "Debug.h"
#include <time.h>

namespace basecross {
	// 静的メンバ変数の実体
	shared_ptr<Debug> Debug::m_ownInstance;

	shared_ptr<Debug> Debug::GetInstance() {
		if (m_ownInstance.get() == 0)
		{
			throw BaseException(
				L"Debugが生成されていません",
				L"if (m_ownInstance.get() == 0)",
				L"Debug::GetInstance()"
			);
		}
		return m_ownInstance;
	}

	void Debug::OnCreate() {
		m_ownInstance = nullptr;
		m_ownInstance = GetThis<Debug>();

		SetDrawLayer(10);
		// 文字列表示用コンポーネント
		m_ssComp = AddComponent<StringSprite>();
		if (m_isShowBackground)
			// 文字列の表示領域の背景色を変更
			m_ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.2));
		// 文字列表示領域のサイズを変更
		m_ssComp->SetTextRect(Rect2D<float>(10, 10, 500, 400));
		m_ssComp->SetText(L"");
	}

	void Debug::OnUpdate() {
		// ログの数を取得
		auto logCount = m_logData.size();
		// ログの数が最大表示数より多い場合は
		// 最新のログから最大表示数までのログを表示する
		if (logCount > m_maxLogCount) {
			int diff = (int)logCount - m_maxLogCount;
			m_displayLogFirstIndex = diff;
		}

		wstring wstr = L"";
		wstr += GetSystemInfo(); // システム情報
		wstr += BorderInsertion(); // 罫線
		if (m_isDisplayForCount) {
			// ログの数
			wstr += L"LogCount : " + Util::SizeTToWStr(m_logData.size()) + L"\n";
			wstr += BorderInsertion(); //罫線
		}
		// ログの表示
		for (int i = m_displayLogFirstIndex; i < logCount; i++) {
			wstr += m_logData[i];
		}
		m_ssComp->SetText(wstr);
	}

	void Debug::Log(const wstring& text) {
		m_logData.push_back(ConvertingToLogData(Type::Normal, text));
	}
	void Debug::WarningLog(const wstring& text) {
		m_logData.push_back(ConvertingToLogData(Type::Warning, text));
	}
	void Debug::ErrorLog(const wstring& text) {
		m_logData.push_back(ConvertingToLogData(Type::Error, text));
	}

	wstring Debug::GetSystemInfo() {
		wstring systemInfo = L"";

		// オブジェクト数
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		systemInfo += L"ObjectCount: " + Util::UintToWStr((UINT)ObjCount) + L"\n";
		// FPS
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		systemInfo += L"FPS: " + Util::UintToWStr(fps);
		systemInfo += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		systemInfo += Util::FloatToWStr(ElapsedTime) + L"\n";

		// フレームカウント
		auto frameCount = App::GetApp()->GetFrameCount();
		systemInfo += L"FrameCount: " + Util::UintToWStr(frameCount) + L"\n";

		// ビューサイズ
		auto viewport = GetStage()->GetView()->GetTargetViewport();
		systemInfo += L"<View>\n";
		systemInfo += L"Width=" + Util::FloatToWStr(viewport.Width, 6, Util::FloatModify::Fixed) + L"\n";
		systemInfo += L"Height=" + Util::FloatToWStr(viewport.Height, 6, Util::FloatModify::Fixed) + L"\n";

		return systemInfo;
	}

	wstring Debug::BorderInsertion() {
		wstring border = L"";
		for (int i = 0; i < 45; i++) {
			border += L"-";
		}
		return border + L"\n";
	}

	wstring Debug::ConvertingToLogData(Type type, wstring text) {
		wstring typeString = L"";
		switch (type)
		{
		case Type::Normal:
			typeString = L"[Normal]";
			break;
		case Type::Warning:
			typeString = L"[Warning]";
			break;
		case Type::Error:
			typeString = L"[Error]";
			break;
		default:
			break;
		}
		return GetNowTimeString() + L" " + typeString + L" " + text + L"\n";;
	}

	wstring Debug::GetNowTimeString() {
		time_t now = time(NULL);
		struct tm pnow;
		localtime_s(&pnow, &now);
		wstring hour = Util::IntToWStr(pnow.tm_hour);
		wstring min = Util::IntToWStr(pnow.tm_min);
		wstring sec = Util::IntToWStr(pnow.tm_sec);
		return L"[" + hour + L":" + min + L":" + sec + L"]";
	}
}
//end basecross