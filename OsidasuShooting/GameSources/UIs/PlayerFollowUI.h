#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class PlayerFollowUI :public BaseUI {
		// UIのタイプ
		enum class UIType {
			Normal,	// 普通
			Bomb,	// 爆弾関係
		};
		// オブジェクトデータ
		struct ObjectData {
			UIType Type;
			shared_ptr<BaseUI> UIObject;
			ObjectData(UIType type, const shared_ptr<BaseUI> ui) {
				this->Type = type;
				this->UIObject = ui;
			}
		};
		// オーナー
		shared_ptr<PlayerBase> m_owner;
		// オブジェクトデータ
		vector<ObjectData> m_objectsData;
		// オフセット
		Vec3 m_offset;
	public:
		PlayerFollowUI(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_owner(player),
			m_offset(Vec3(0.0f, 0.0f, 0.0f))
		{
			SetTransformInit(false);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};

	class PlayerPositionUI :public BaseUI {
		// オーナー
		shared_ptr<PlayerBase> m_owner;
		// オフセット
		Vec3 m_offset;
		vector<shared_ptr<BaseUI>> m_uiObject;
		/**
		 * @brief 画面内にクランプ
		 *
		 * @param value ベクトル
		 * @return 画面内にクランプされたベクトル
		 */
		Vec3 ClampInScreen(const Vec3& value);
	public:
		PlayerPositionUI(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_owner(player),
			m_offset(Vec3(0.0f, 0.0f, 0.0f))
		{
			SetTransformInit(false);
		}
		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
