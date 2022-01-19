#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Confetti::OnCreate() {
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Confetti");
		efkComp->Play(L"Confetti");
	}
	void Confetti::OnDestroy() {
		GetComponent<EfkComponent>()->StopAll();
	}
}