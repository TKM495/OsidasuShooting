#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// インスタンスの初期化
	unique_ptr<PlayerStatus, PlayerStatus::Deleter> PlayerStatus::m_instance = nullptr;

	void PlayerStatus::DataExtraction() {
		// XMLのデータを取得
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		// プレイヤーの色情報を取得
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/PlayerColor");
		// 4プレイヤー分の色を空白で4つのデータに分ける
		auto colorStrVec = DataExtracter::DelimitData(data, L' ');
		for (int i = 0; i < 4; i++) {
			// 自身のプレイヤー番号に応じた色データをRGBAに分類
			auto colorStr = DataExtracter::DelimitData(colorStrVec[i]);
			// 分類したものをCol4に変換
			auto color = DataExtracter::ColorDataExtraction(colorStr);
			// 0～1に変換
			m_colorTable[PlayerNumber(i)] = Utility::ConvertColorZeroToOne(color);
		}
	}

	Col4 PlayerStatus::GetPlayerColor(PlayerNumber number) {
		return m_colorTable[number];
	}
	Col4 PlayerStatus::GetPlayerColor(int number) {
		return GetPlayerColor(PlayerNumber(number - 1));
	}
}