/*!
@file   LifeSpan.cpp
@brief  寿命を持たせるためのコンポーネントの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LifeSpan::OnUpdate() {
		if (m_timer.Count()) {
			// このコンポーネントのオーナーを削除
			GetGameObject()->GetStage()->RemoveGameObject<GameObject>(GetGameObject());
		}
	}
}