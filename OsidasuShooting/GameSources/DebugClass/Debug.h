/*!
@file   Debug.h
@brief  デバッグクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Debug :public GameObject {
	private:
		/**
		 * @brief ログの種類
		 */
		enum class Type {
			Normal,		// 通常
			Warning,	// 警告
			Error		// エラー
		};
		// ログのデータ本体
		vector<wstring> m_logData;
		// 表示するログの最初のインデックス
		int m_displayLogFirstIndex;
		// StringSpriteコンポーネント
		shared_ptr<StringSprite> m_ssComp;
		// 自身のインスタンス
		static shared_ptr<Debug> m_ownInstance;

		/**
		 * @brief ログデータに変換
		 *
		 * @param type	タイプ
		 * @param text	テキスト
		 * @return 1行分のログの文字列
		 */
		wstring ConvertingToLogData(Type type, wstring text);
		/**
		 * @brief 現在の時間を文字列で取得
		 *
		 * @return 現在の時間の文字列
		 */
		wstring GetNowTimeString();
		/**
		 * @brief システムの情報を文字列で取得
		 *
		 * @return システムの情報(文字列)
		 */
		wstring GetSystemInfo();
		/**
		 * @brief 罫線を取得
		 *
		 * @return 1行分の罫線の文字列
		 */
		wstring BorderInsertion();
	private: // 以下設定
		// 表示するログの最大数
		int m_maxLogCount;
		// ログの数を表示するか
		bool m_isDisplayForCount;
		// 背景を表示するか
		bool m_isShowBackground;
	public:
		Debug(const shared_ptr<Stage>& stage)
			:GameObject(stage), m_displayLogFirstIndex(0),
			// 以下設定
			m_maxLogCount(18),
			m_isDisplayForCount(true),
			m_isShowBackground(false)
		{}

		void OnCreate();
		void OnUpdate();

		/**
		 * @brief 通常のログを出力
		 *
		 * @param text ログとして出す文字列
		 */
		void Log(const wstring& text);
		/**
		 * @brief 警告のログを出力
		 *
		 * @param text ログとして出す文字列
		 */
		void WarningLog(const wstring& text);
		/**
		 * @brief エラーのログを出力
		 *
		 * @param text ログとして出す文字列
		 */
		void ErrorLog(const wstring& text);

		/**
		 * @brief Debugのインスタンスを取得
		 *
		 * @return shared_ptr<Debug>
		 */
		static shared_ptr<Debug> GetInstance();
	};
}
//end basecross