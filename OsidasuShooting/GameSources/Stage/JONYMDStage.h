/*!
@file   JONYMDStage.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class JONYMDStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		JONYMDStage() :Stage() {}
		virtual ~JONYMDStage() {}
		//������
		virtual void OnCreate()override;
	};
}
