#pragma once
#include "stdafx.h"

namespace basecross {

	class ItemsCreations : public GameObject
	{
	private:
		float time;//時間は秒です。

		float countDown;

		Vec3 spawnScale;
		vector<Vec3> areaPosition;

		void AreaPosition();
		void AdjustingAreaPosition();
		void SpawnInRandomPosition();
		void SetSpawnScale();

	public:
		ItemsCreations(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void Spawn(); //生成される
		void StopSpawn();//生成されない
	};

}
