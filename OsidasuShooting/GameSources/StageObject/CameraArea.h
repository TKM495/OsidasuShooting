#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	class CameraArea :public AdvancedGameObject {
	private:
		// ƒGƒŠƒA
		Vec2 m_area;
	public:
		CameraArea(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
	};
}
