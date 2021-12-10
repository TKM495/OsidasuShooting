#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void MeteoriteCreation::OnCreate()
	{
		auto stage = GetStage();
		auto cameraSelect = stage->GetView()->GetTargetCamera();

		camera = dynamic_pointer_cast<Camera>(cameraSelect);
		if (camera)
		{
			originalEye = camera->GetEye();
			originalAt = camera->GetAt();
		}


	}

	void MeteoriteCreation::Spawn()
	{
		GetStage()->AddGameObject<Meteorite>();
		
	}

}

