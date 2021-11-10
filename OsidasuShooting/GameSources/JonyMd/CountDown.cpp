#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void CountDown::OnCreate()
	{
		currentTime = initialTime;
	}


	void CountDown::OnUpdate()
	{
		auto& app = App::GetApp();
		float deltaTime = app->GetElapsedTime();

		int minutes;
		int hour;
		int seconds;
		
		wstring clocks = L"00:00:00";

		if (reset)
		{
			currentTime = initialTime;
			reset = false;
		}

		if (start)
		{
			currentTime -= deltaTime;
		}


		minutes = (int)(currentTime / 60);
		hour = (int)(minutes / 60);
		seconds = currentTime - (hour * 60 + minutes) * 60;

		clocks = L"";
		if (hour <= 9)
		{
			clocks += L"0";
		}
		clocks += Util::FloatToWStr(hour) + L":";

		if (minutes <= 9)
		{
			clocks += L"0";
		}
		clocks += Util::FloatToWStr(minutes) + L":";

		if (seconds <= 9)
		{
			clocks += L"0";
		}
		clocks += Util::FloatToWStr(seconds);



		auto m_ssComp = AddComponent<StringSprite>();
		m_ssComp->SetText(clocks);
	}



}
