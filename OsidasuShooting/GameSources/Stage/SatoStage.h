/*!
@file   SatoStage.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "JonyMd/CountDown.h"

namespace basecross {
	class SatoStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		SatoStage() :Stage() {}
		virtual ~SatoStage() {}
		//������

		void SetPlayer();
		virtual void OnCreate()override;

		shared_ptr<CountDown> m_timer;
	};
}
