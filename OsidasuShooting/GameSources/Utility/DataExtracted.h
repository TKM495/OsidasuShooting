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

	struct Extracter {
		/**
		 * @brief 1行のCSVデータを配列に格納
		 *
		 * @param line 1行のCSVデータ
		 * @return 配列
		 */
		static vector<wstring> DelimitData(const wstring& line) {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, line, L',');
			return tokens;
		}

		/**
		 * @brief トランスフォームデータを抽出
		 *
		 * @param tokens
		 * @return
		 */
		static TransformData TransformDataExtraction(const vector<wstring>& tokens) {
			TransformData data;
			data.Position = Vec3(
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str()),
				(float)_wtof(tokens[3].c_str())
			);
			data.Scale = Vec3(
				(float)_wtof(tokens[4].c_str()),
				(float)_wtof(tokens[5].c_str()),
				(float)_wtof(tokens[6].c_str())
			);
			data.Rotation = Vec3(
				XMConvertToRadians((float)_wtof(tokens[7].c_str())),
				XMConvertToRadians((float)_wtof(tokens[8].c_str())),
				XMConvertToRadians((float)_wtof(tokens[9].c_str()))
			);
			return data;
		}
	};
}
