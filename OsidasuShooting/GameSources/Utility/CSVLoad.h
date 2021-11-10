/*!
@file   CSVLoad.h
@brief  CSVからデータを取り出すクラス
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	// スプライトのデータ形式
	struct SpriteDataFormat {
		wstring name;	// 名称
		Vec2 origin;	// 原点の座標
		Vec2 size;		// サイズ
	};

	// スプライトのタイプ
	enum class SpriteType {
		String,
		Image,
		Number
	};

	class CSVLoad :public GameObject {
		// スプライトデータの配列
		vector<SpriteDataFormat> m_stringSpriteData;
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージ
		 */
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		/**
		 * @brief データの取り出し
		 *
		 * @param fileData	ファイルデータ
		 * @param type		スプライトのタイプ
		 */
		void SpriteDataExtraction(vector<wstring> fileData, SpriteType type);

		/**
		 * @brief スプライトデータの取得
		 *
		 * @return スプライトデータ
		 */
		vector<SpriteDataFormat>& GetStringSpriteData() {
			return m_stringSpriteData;
		}
	};
}
//end basecross