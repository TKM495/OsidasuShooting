#pragma once
#include "stdafx.h"

namespace basecross {

	class ListsOfVariable : public GameObject
	{
	public:
		float executeTime = 10.0f; //ゲームオブジェクトが生成から一定時間経過した場合も消えるため
		float speed = 5.0f; //たとえば、プレイヤーオブジェクトから設定された速度
		Vec3 direction = Vec3(1,0,0);//たとえば、プレイヤーオブジェクトから設定された方向

		ListsOfVariable(const shared_ptr <Stage>& stage)
			:GameObject(stage)
		{}
	};

}
