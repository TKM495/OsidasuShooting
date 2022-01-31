#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	namespace modifiedClass {
		class Fencing : public AdvancedGameObject
		{
			enum class Status {
				Showing,
				BlinkingToHide,
				Hiding,
				BlinkingToShow,
			};

			Status status = Fencing::Status::Showing;

			float blinkingTime;
			float blinkShowTime;
			float blinkHideTime;

			float showTime;
			float hideTime;

			float timeChecker = 0.0f;

		public:
			Fencing(const shared_ptr<Stage>& stage, const wstring& line);

			void OnCreate() override;
			void OnUpdate() override;
		};
	}
}
