#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BaseUI::OnPreCreate() {
		GameObject::OnPreCreate();
		ApplyTransform();
	}

	void BaseUI::ApplyTransform() {
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_localTransData.Position);
		transComp->SetScale(m_localTransData.Scale);
		transComp->SetRotation(m_localTransData.Rotation);
	}
}