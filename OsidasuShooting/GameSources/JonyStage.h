#pragma once
#include "stdafx.h"

namespace basecross {

	class JonyStage : public Stage {

		// �J�����ƃ��C�g�֘A
		void CreateViewLight();

	public:
		JonyStage() :Stage() {}

		virtual ~JonyStage() {}

//override Funtions
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
//override Funtions...end


		// �Ⴄ�X�e�[�W�ɐ؂�ւ���
		void ChangeToAnotherStage();
	};
}