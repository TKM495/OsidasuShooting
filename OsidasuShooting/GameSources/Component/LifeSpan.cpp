/*!
@file   LifeSpan.cpp
@brief  �������������邽�߂̃R���|�[�l���g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LifeSpan::OnUpdate() {
		if (m_timer.Count()) {
			// ���̃R���|�[�l���g�̃I�[�i�[���폜
			GetGameObject()->GetStage()->RemoveGameObject<GameObject>(GetGameObject());
		}
	}
}