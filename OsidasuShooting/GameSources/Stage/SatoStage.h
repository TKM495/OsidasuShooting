/*!
@file   SatoStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SatoStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		SatoStage() :Stage() {}
		virtual ~SatoStage() {}
		//������
		virtual void OnCreate()override;
	};
}
