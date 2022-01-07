#pragma once
#include "stdafx.h"

namespace basecross {

	class Fencing : public GameObject
	{

		//以下の変数は秒です
		int show;
		int hide;
		int start;

		//何回、消えたり現れたりをするか
		//　０　は一回だけ
		//　＞０　は値まで
		//　＜０　は無制限
		int repeat;

		//　初めてhide、そしてshowが終わったらtotalRepeatedの値が上がります
		int totalRepeated;


		//現在の秒
		float countDown;


		//現在の進展
		enum Status
		{
			Show,
			Hide,
			Start,
			Stop,
		};
		Status status;


	public:
		Fencing(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

}
