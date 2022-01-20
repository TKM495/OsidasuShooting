/*!
@file   WatanabeStage.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "Utility/GameController.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	class WatanabeStage : public Stage {
		GameController m_controller;
		//ビューの作成
		void CreateViewLight();
		// アイテム生成オブジェクト
		shared_ptr<modifiedClass::ItemCreation> m_itemCreation;

	public:
		//構築と破棄
		WatanabeStage() :Stage(), m_controller(PlayerNumber::P1) {}
		virtual ~WatanabeStage() {}
		//初期化
		virtual void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};
}
