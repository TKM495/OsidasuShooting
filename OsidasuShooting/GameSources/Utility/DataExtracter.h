#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	// スプライトのデータ形式
	struct SpriteDataFormat {
		wstring name;	// 名称
		Vec2 origin;	// 原点の座標
		Vec2 size;		// サイズ
	};

	/**
	 * @brief 文字列の配列から各種データを抽出するクラス
	 */
	struct DataExtracter {
		/**
		 * @brief 1行のCSVデータを配列に格納
		 *
		 * @param line 1行のCSVデータ
		 * @return 配列
		 */
		static vector<wstring> DelimitData(const wstring& line, wchar_t delimiter = L',') {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, line, delimiter);
			return tokens;
		}

		/**
		 * @brief トランスフォームデータを抽出
		 *
		 * @param tokens 文字列
		 * @param firstIndex 最初のインデックス（デフォルト：1）
		 * @return トランスフォームデータ
		 */
		static TransformData TransformDataExtraction(const vector<wstring>& tokens, size_t firstIndex = 1) {
			TransformData data;
			data.Position = Vec3(
				(float)_wtof(tokens[firstIndex].c_str()),
				(float)_wtof(tokens[firstIndex + 1].c_str()),
				(float)_wtof(tokens[firstIndex + 2].c_str())
			);
			data.Scale = Vec3(
				(float)_wtof(tokens[firstIndex + 3].c_str()),
				(float)_wtof(tokens[firstIndex + 4].c_str()),
				(float)_wtof(tokens[firstIndex + 5].c_str())
			);
			data.Rotation = Vec3(
				XMConvertToRadians((float)_wtof(tokens[firstIndex + 6].c_str())),
				XMConvertToRadians((float)_wtof(tokens[firstIndex + 7].c_str())),
				XMConvertToRadians((float)_wtof(tokens[firstIndex + 8].c_str()))
			);
			return data;
		}

		/**
		 * @brief カラーデータを抽出
		 *
		 * @param tokens 文字列
		 * @return カラーデータ
		 */
		static Col4 ColorDataExtraction(const vector<wstring>& tokens)
		{
			Col4 color;
			color = Col4(
				(float)_wtof(tokens[0].c_str()),
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str()),
				(float)_wtof(tokens[3].c_str())
			);
			return color;
		};
	};
}
