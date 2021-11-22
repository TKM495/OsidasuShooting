/*!
@file   CSVLoad.h
@brief  CSVからデータを取り出すクラス
 */

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	// スプライトのデータ形式
	struct SpriteDataFormat {
		wstring name;	// 名称
		Vec2 origin;	// 原点の座標
		Vec2 size;		// サイズ
	};

	class CSVLoad :public BaseSingleton<CSVLoad> {
	private:
		CSVLoad() {}
		~CSVLoad() {}
		friend class BaseSingleton<CSVLoad>;
	private:
		// データ
		map<wstring, vector<wstring>> m_data;
	public:
		/**
		 * @brief ファイルを登録する
		 */
		void RegisterFile(const wstring& key, const wstring& filePath);
		/**
		 * @brief データを取得する
		 */
		void GetData(const wstring& key);
	};
}
//end basecross