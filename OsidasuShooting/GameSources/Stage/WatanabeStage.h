/*!
@file   WatanabeStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WatanabeStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		WatanabeStage() :Stage() {}
		virtual ~WatanabeStage() {}
		//������
		virtual void OnCreate()override;
	};
}
