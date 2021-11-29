/*!
@file   CSVLoad.h
@brief  CSVのデータを管理するクラス
 */

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	// シングルトン
	class CSVLoad :public BaseSingleton<CSVLoad> {
	private:
		CSVLoad() {}
		~CSVLoad() {}
		friend class BaseSingleton<CSVLoad>;
	private:
		// データ（キー,データ）
		map<wstring, vector<wstring>> m_data;
	public:
		/**
		 * @brief ファイルを登録する
		 *
		 * @param key キー
		 * @param filePath ファイルパス
		 */
		void RegisterFile(const wstring& key, const wstring& filePath);

		/**
		 * @brief データを取得する
		 *
		 * @param key キー
		 * @return キーに紐づいているデータ
		 */
		vector<wstring> GetData(const wstring& key)const;

		/**
		 * @brief キーが存在するか
		 *
		 * @param key キー
		 * @return すでに存在している場合true
		 */
		bool CheckData(const wstring& key);
	};
}
//end basecross