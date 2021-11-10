#pragma once
#include "stdafx.h"

namespace basecross {

	class CountDown : public GameObject
	{
	private:
		bool start = false;
		bool reset;

		float initialTime = 180.0f; //•b‚Ì’l‚Å‚·
		float currentTime;

	public:
		CountDown(const shared_ptr <Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void Start() {
			start = true;
		}
		void Stop() {
			start = false;
		}
		void Reset() {
			reset = true;
		}



		void Adjust(float adjust) {
			currentTime += adjust;
			if (currentTime > initialTime)
			{
				currentTime = initialTime;
			}
			else if (currentTime < 0)
			{
				currentTime = 0;
			}
		}
		//void ClockCreation();
	};

}
