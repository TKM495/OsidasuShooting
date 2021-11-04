/*!
@file CameraTester.h
@brief �J�����̃e�X�g�̃^�[�Q�b�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	// �ǐՂ̑Ώ�
	class TargetObj : public GameObject {
	public:
		TargetObj(const shared_ptr<Stage>& stage);
		virtual ~TargetObj() {};
		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross