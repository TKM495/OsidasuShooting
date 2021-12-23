/*!
@file   FallDecision.h
@brief  �G�ꂽ�痎������Ƃ���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class FallDecision :public AdvancedGameObject {
	public:
		FallDecision(const shared_ptr<Stage>& stage);
		FallDecision(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
