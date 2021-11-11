/*!
@file   CSVLoad.cpp
@brief  CSVからデータを取り出すクラス実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CSVLoad::SpriteDataExtraction(vector<wstring> fileData, SpriteType type) {
		if (fileData.size() == 0) {
			throw BaseException(
				L"データがありません",
				L"Size : " + to_wstring(fileData.size()),
				L"CSVLoad::SpriteDataExtraction()"
			);
		}
		// 0番目(1行目)は見出しなので除外
		for (size_t i = 1; i < fileData.size(); i++) {
			// トークン（カラム）の配列
			vector<wstring> tokens;

			// トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(tokens, fileData[i], L',');

			// 構造体にデータを格納
			SpriteDataFormat data;
			data.name = tokens[0];
			data.origin = Vec2(
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str())
			);
			data.size = Vec2(
				(float)_wtof(tokens[3].c_str()),
				(float)_wtof(tokens[4].c_str())
			);

			// タイプごとの配列にデータを格納
			switch (type)
			{
			case SpriteType::String:
				m_stringSpriteData.push_back(data);
				break;
			case SpriteType::Image:
				break;
			case SpriteType::Number:
				break;
			default:
				break;
			}
		}
	}
}
//end basecross