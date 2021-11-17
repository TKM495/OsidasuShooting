#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void AdvancedGameObject::OnPreCreate() {
		GameObject::OnPreCreate();
		if (m_isTransformInit)
			ApplyTransform();
	}

	void AdvancedGameObject::ApplyTransform() {
		auto transComp = GetTransform();
		transComp->SetPosition(m_transformData.Position);
		transComp->SetScale(m_transformData.Scale);
		transComp->SetRotation(m_transformData.Rotation);
	}
}