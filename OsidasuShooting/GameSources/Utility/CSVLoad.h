/*!
@file   CSVLoad.h
@brief  CSVからデータを取り出すクラス
 */

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
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
		vector<wstring> GetData(const wstring& key)const;
	};
}
//end basecross