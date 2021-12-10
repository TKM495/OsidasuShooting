#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ShackingCamera::OnCreate()
	{
		GetComponent<Transform>()->SetPosition(10,12,14);

		auto stage = GetStage();
		auto cameraSelect = stage->GetView()->GetTargetCamera();

		camera = dynamic_pointer_cast<Camera>(cameraSelect);
		if (camera)
		{
			eye = originalEye = camera->GetEye();
			at = originalAt = camera->GetAt();
		}


	}

	void ShackingCamera::OnUpdate()
	{
		if (curShackingCount > shackingCount)
		{
			GetStage()->RemoveGameObject<ShackingCamera>(GetThis<ShackingCamera>());
			return;
		}

		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();


		speed += speed * speedincrease / 100;
		ShackingLeftRight(deltaTime);

		camera->SetEye(eye);
		camera->SetAt(at);

	}


	void ShackingCamera::OnDestroy()
	{
		camera->SetEye(originalEye);
		camera->SetAt(originalAt);
	}



	void ShackingCamera::ShackingLeftRight(float deltaTime)
	{

		if (!isMin && !isMax && !isOri)
		{
			isMin = true;
		}

		if (isMin)
		{
			if (eye.x > originalEye.x + min.x)
			{
				eye.x -= deltaTime * speed;
				at.x -= deltaTime * speed;
			}
			else
			{
				isMin = false;
				isMax = true;
			}
		}


		if (isMax)
		{
			if (eye.x < originalEye.x + max.x)
			{
				eye.x += deltaTime * speed;
				at.x += deltaTime * speed;

			}
			else
			{
				isMin = false;
				isMax = false;
				isOri = true;
			}
		}


		if (isOri)
		{
			if (eye.x >= originalEye.x)
			{
				eye.x -= deltaTime * speed;
				at.x -= deltaTime * speed;

			}
			else
			{
				eye.x = originalEye.x;
				at.x = originalAt.x;
				isMin = false;
				isMax = false;
				isOri = false; 
				curShackingCount++;
			}
		}




	}//ShackingLeftRight...end
}
