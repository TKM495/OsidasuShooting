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
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		WatanabeStage() :Stage(), m_controller(PlayerNumber::P1) {}
		virtual ~WatanabeStage() {}
		//������
		virtual void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};
}
