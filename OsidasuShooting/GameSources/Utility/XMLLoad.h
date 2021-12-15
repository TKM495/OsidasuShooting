#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class XMLLoad :public BaseSingleton<XMLLoad> {
	private:
		XMLLoad() :BaseSingleton() {}
		~XMLLoad() {}
		friend class BaseSingleton<XMLLoad>;
	private:
		// データ（キー,データ）
		map<wstring, shared_ptr<XmlDocReader>> m_data;
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
		shared_ptr<XmlDocReader> GetData(const wstring& key)const;
	};

	struct XMLHelper {
		static wstring GetSingleNodeWString(const shared_ptr<XmlDocReader>& reader, const wstring nodeText);
	};
}
