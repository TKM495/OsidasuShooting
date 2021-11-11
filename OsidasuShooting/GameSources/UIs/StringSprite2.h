/*!
@file   StringSprite2.h
@brief  文字列表示用クラス
 */

#pragma once
#include "stdafx.h"
#include "Utility/CSVLoad.h"
#include "Component/FadeComponent.h"
#include "UIHeader.h"

namespace basecross {
	class StringSprite2 :public GameObject {
		// 時間計測用
		float m_delta;
		// 非アクティブになるまでの時間
		float m_deActiveTime;
		// 非アクティブかどうか
		bool m_bDeactive;
		// 色
		Col4 m_color;
		// 自分のデータ
		SpriteDataFormat m_data;
		// 表示する文字の名前
		wstring m_name;
		// 横の設定
		Align::Horizontal m_horizontal;
		// 縦の設定
		Align::Vertical m_vertical;
		// 頂点データ
		vector<VertexPositionColorTexture> vertices;

		int SearchDataIndex(const vector<SpriteDataFormat>& data);
	public:
		/**
		 * @brief コンストラクタ
		 *
		 * @param stage ステージ
		 * @param name 表示するテクスチャ
		 * @param horizontal 水平位置
		 * @param vertical 垂直位置
		 * @param color 色
		 */
		StringSprite2(const shared_ptr<Stage>& stage,
			wstring name,
			Align::Horizontal horizontal = Align::Horizontal::Center,
			Align::Vertical vertical = Align::Vertical::Center,
			Col4 color = Col4(0.0f, 0.0f, 0.0f, 1.0f))
			:GameObject(stage),
			m_name(name),
			m_horizontal(horizontal),
			m_vertical(vertical),
			m_color(color),
			m_delta(0.0f),
			m_deActiveTime(0.0f),
			m_bDeactive(false)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		/**
		 * @brief 水平方向の設定
		 *
		 * @param hor 水平方向の位置
		 */
		void SetAlignHorizontal(Align::Horizontal hor);
		/**
		 * @brief 垂直方向の設定
		 *
		 * @param ver 垂直方向の位置
		 */
		void SetAlignVertical(Align::Vertical ver);

		/**
		 * @brief サイズの設定
		 *
		 * @param size サイズ
		 */
		void SetSize(float size);
		/**
		 * @brief 位置の設定
		 *
		 * @param pos 位置
		 */
		void SetPos(Vec2 pos);

		/**
		 * @brief サイズの取得
		 *
		 * @return サイズ
		 */
		float GetSize();
		/**
		 * @brief 位置の取得
		 *
		 * @return 位置
		 */
		Vec3 GetPos();

		/**
		 * @brief テクスチャサイズの取得
		 *
		 * @return テクスチャサイズ
		 */
		Vec2 GetTexSize() {
			return m_data.size;
		}

		/**
		 * @brief フェードコンポーネントの取得
		 *
		 * @return フェードコンポーネント
		 */
		shared_ptr<FadeComponent> GetFadeComp() {
			return GetComponent<FadeComponent>();
		}

		/**
		 * @brief 色の設定
		 *
		 * @param color 色
		 */
		void SetColor(Col4 color);
		/**
		 * @brief 色の取得
		 *
		 * @return 色
		 */
		Col4 GetColor() {
			return m_color;
		}

		/**
		 * @brief 非アクティブにする
		 *
		 * @param time 非アクティブまでの時間
		 */
		void Deactive(float time) {
			m_deActiveTime = time;
			SetUpdateActive(true);
		}
		/**
		 * @brief 非アクティブにする
		 */
		void Deactive() {
			Deactive(0.0f);
		}
	};
}
//end basecross
