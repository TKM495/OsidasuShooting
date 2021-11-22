#pragma once
#include "stdafx.h"

namespace basecross {

	class Items: public GameObject
	{
	public:
		wstring name = L"Items";
		Items(const shared_ptr<Stage>&stage)
			: GameObject(stage)
		{}

		void OnCreate() override;
	};

}
