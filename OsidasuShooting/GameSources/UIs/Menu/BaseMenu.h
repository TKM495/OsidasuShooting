/*!
@file   BaseMenu.h
@brief  メニューの基底クラス
 */

#pragma once
#include "Cursor.h"
#include "UIs/StringSprite2.h"
#include "stdafx.h"

namespace basecross {
	// メニュー項目の表示に必要な構造体を用意する
	struct MenuElement {
		Vec2 pos;        // 座標格納用変数
		wstring name;    // 項目名格納用変数
		wstring sendMsg; // 送るメッセージ
		bool flg = true; // 有効無効
	};

	class BaseMenu : public GameObject {
	protected:
		// カーソルの移動方向
		enum class MenuDirection {
			Vertical,  //垂直方向
			Horizontal //水平方向
		};

	private:
		// メニュー要素のベクター配列
		vector<MenuElement> m_menuElement;
		// メニューの文字
		vector<shared_ptr<StringSprite2>> m_stringSprite;
		// メニューの文字のフレーム
		//vector<shared_ptr<illusionFrame>> m_illusionFrame;
		// オーディオ取得用
		shared_ptr<XAudio2Manager> m_audio;
		// メニューの要素数
		int m_menuNum;
		// 今選択しているメニュー
		int m_nowMenuNum;
		// カーソルの移動方向
		MenuDirection m_dir;
		// 遷移遅延
		float m_delayTime;
		// 遷移フラグ
		bool m_bChange;
		// 遅延時間計測用
		float m_delayDelta;
		// 点滅の時間計測用
		float m_delta;
		// 点滅のレート
		float m_rate;
		// カーソルの移動速度
		float m_cursorSp;
		// メニューの現在の状態
		bool m_bActive;
		// カーソルアクティブ時の色
		Col4 m_activeCol;
		// メニューの描画レイヤー
		int m_drawLayer;
		/**
		 * @brief 描画レイヤーのリセット
		 *
		 * @param layer 描画するレイヤー
		 */
		void ResetDrawLayer(int layer);
	protected:
		/**
		 * @brief メニュー構築
		 */
		void SetUpMenu();
		/**
		 * @brief ボタンが押されたときの処理
		 *
		 * @param element 選択されたメニュー要素
		 */
		virtual void OnPushButton(MenuElement element);
		/**
		 * @brief ボタンが押されたときの処理
		 *
		 * @param mes 選択されたメニューが持つMenuElementのsendMsg
		 */
		virtual void OnPushButton(wstring mes);
		/**
		 * @brief ボタンが押されたときの処理
		 */
		virtual void OnPushButton();
		/**
		 * @brief シーンが遷移するときの処理
		 *
		 * @param mes 送るメッセージ
		 */
		virtual void SendEvent(wstring mes);
		/**
		 * @brief リセット前の処理
		 */
		virtual void BeforeReset() {}
		/**
		 * @brief 選択音の再生
		 */
		virtual void PlayDecisionSE();
		/**
		 * @brief 選択音の再生
		 *
		 * @param mes 送ったメッセージ
		 */
		virtual void PlayDecisionSE(wstring mes);
		/**
		 * @brief ボタンが押されてから遷移までの時間の設定
		 *
		 * @param time 遷移するまでの時間
		 */
		void SetDelayTime(float time) {
			m_delayTime = time;
		}
		/**
		 * @brief メニュー要素を配列に入れる
		 *
		 * @param element 入れるメニュー要素
		 */
		void PushBackElement(const MenuElement& element) {
			m_menuElement.push_back(element);
		}
		/**
		 * @brief メニューの移動方向の設定
		 *
		 * @param dir 移動方向
		 */
		void SetMenuDirection(MenuDirection dir) {
			m_dir = dir;
		}
		/**
		 * @brief 遷移フラグが立っているか
		 *
		 * @return 立っていればtrue/立っていないときはfalse
		 */
		bool IsChange() {
			return m_bChange;
		}
		/**
		 * @brief すべてのメニュー要素の取得
		 *
		 * @return メニュー要素のベクター配列
		 */
		vector<MenuElement>& GetMenuElement() {
			return m_menuElement;
		}

	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージ
		 */
		BaseMenu(const shared_ptr<Stage>& stage)
			: GameObject(stage),
			m_menuNum(0),
			m_nowMenuNum(0),
			m_dir(MenuDirection::Vertical),
			m_delayTime(0.0f),
			m_bChange(false),
			m_delayDelta(0.0f),
			m_delta(0.0f),
			m_cursorSp(10.0f),
			m_audio(App::GetApp()->GetXAudio2Manager()),
			m_bActive(true),
			m_rate(4.0f),
			m_activeCol(Col4(240.0f, 168.0f, 0.0f, 1.0f) / 255.0f),
			m_drawLayer(0) {}

		virtual void OnCreate() override {}
		virtual void OnUpdate() override;

		/**
		 * @brief メニューの表示、非表示
		 *
		 * @param flg true:表示/false:非表示
		 */
		void SetDrawMenu(bool flg);
		/**
		 * @brief リセット
		 */
		virtual void Reset();

		/**
		 * @brief メニューの描画レイヤーの設定
		 *
		 * @param layer 描画レイヤー
		 */
		void SetMenuDrawLayer(int layer) {
			m_drawLayer = layer;
			ResetDrawLayer(m_drawLayer);
		}
	};
}
//end basecross
