//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void FenceController::ControllingFence()
	{
		bool doDestroy = false;
		switch (status)
		{
		case FenceController::Status::Show:
			GetStage()->AddGameObject<Fencing>();
			break;
		case FenceController::Status::Hide:
			doDestroy = true;
			break;
		default:
			break;

		}

		if (doDestroy)
		{
			auto objs = GetStage()->GetGameObjectVec();
			for (auto& obj : objs)
			{
				auto fencing = dynamic_pointer_cast<Fencing>(obj);
				GetStage()->RemoveGameObject<Fencing>(fencing);
			}
		}

	}









	void FenceController::OnCreate()
	{
		start = 3;
		show = 10;
		hide = 6;

		countDown = start;
		repeat = -1;
		totalRepeated = 0;

		status = FenceController::Status::Start;

		auto ssComp = AddComponent<StringSprite>();
	}


	void FenceController::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();
		bool isFenceControll = false;

		if (countDown < 0)
		{
			bool tohide = false;
			switch (status)
			{
			case FenceController::Status::Show:
				totalRepeated++;
				if (repeat<0)
				{
					tohide = true;
				}
				else if (repeat > totalRepeated)
				{
					tohide = true;
				}
				else
				{
					status = FenceController::Status::Stop;
					countDown = 0;
					SetUpdateActive(false);
				}
				break;
			case FenceController::Status::Hide:
				isFenceControll = true;
				status = FenceController::Status::Show;
				countDown = show;
				currentStatus = L"Show";
				break;
			case FenceController::Status::Start:
				tohide = true;
				break;
			default:
				break;
			}

			if (tohide)
			{
				isFenceControll = true;
				status = FenceController::Status::Hide;
				countDown = hide;
				currentStatus = L"Hide";
			}
		}


		if (countDown > 0) 
		{
			countDown -= deltaTime;
			wstring text = currentStatus + L"\ncountDown: " + Util::FloatToWStr((int)countDown) + L"\nTotal Repeated " + Util::IntToWStr(totalRepeated);
			auto ssComp = GetComponent<StringSprite>();//must have AddComponent in onCreate function
			ssComp->SetText(text);
		}



		//Show ‚Æ Hide ‚ÌŽÀ‘•
		if (isFenceControll)
		{
			ControllingFence();
		}

	}
}
