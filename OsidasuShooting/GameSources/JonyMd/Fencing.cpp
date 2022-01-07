//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Fencing::OnCreate()
	{
		start = 3;
		show = 10;
		hide = 6;

		repeat = -1;// <0 ‚Í–³§ŒÀ
		totalRepeated = 0;

		status = Fencing::Status::Start;
		switch (Fencing::status)
		{
		case Fencing::Status::Show:
			countDown = show;
			break;
		case Fencing::Status::Hide:
			countDown = hide;
			SetDrawActive(false);
			break;
		case Fencing::Status::Start:
			countDown = start;
			break;
		case Fencing::Status::Stop:
			SetUpdateActive(false);
			break;
		default:
			break;
		}




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



	void Fencing::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		if (countDown < 0)
		{
			bool ishide = false;
			switch (Fencing::status)
			{
			case Fencing::Status::Show:
				totalRepeated++;
				if (repeat < 0 || repeat > totalRepeated)
				{
					ishide = true;
				}
				else
				{
					status = Fencing::Status::Stop;
					SetUpdateActive(false);
				}
				break;
			case Fencing::Status::Hide:
				SetDrawActive(true);
				status = Fencing::Status::Show;
				countDown = show;
				break;
			case Fencing::Status::Start:
				ishide = true;
				break;
			default:
				break;
			}

			if (ishide)
			{
				SetDrawActive(false);
				status = Fencing::Status::Hide;
				countDown = hide;
			}
		}


		if (countDown > 0)
		{
			countDown -= deltaTime;
		}


	}



}
