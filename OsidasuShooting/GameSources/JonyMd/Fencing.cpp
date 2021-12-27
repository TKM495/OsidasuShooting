//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Fencing::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transform = GetComponent<Transform>();

		Vec3 position = transform->GetPosition();
		Vec3 scale = transform->GetScale();



		position = Vec3(0,0,0);
		scale = Vec3(10,1,10);


		transform->SetPosition(position);
		transform->SetScale(scale);


	}
}
