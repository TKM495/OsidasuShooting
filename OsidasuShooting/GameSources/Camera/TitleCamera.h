#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleCamera :public Camera {
	public:
		TitleCamera() :Camera() {}
		void OnCreate()override;
		void OnUpdate()override;
	};
}
