/*!
@file   WatanabeStage2.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WatanabeStage2 : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		WatanabeStage2() :Stage() {}
		virtual ~WatanabeStage2() {}
		//������
		virtual void OnCreate()override;
		void OnUpdate()override;
	};
}
