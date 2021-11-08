#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageObject::ObjectSetUp() {
		auto transComp = GetTransform();
		transComp->SetPosition(m_transformData.Position);
		transComp->SetScale(m_transformData.Scale);
		transComp->SetRotation(m_transformData.Rotation);
		AddTag(L"StageObject");
	}

	shared_ptr<Transform> StageObject::GetTransform() {
		return GetComponent<Transform>();
	}
}