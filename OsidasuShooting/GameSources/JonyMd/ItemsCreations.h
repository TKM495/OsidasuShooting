#pragma once
#include "stdafx.h"

namespace basecross {

	class ItemsCreations : public GameObject
	{
	private:
		float time;//���Ԃ͕b�ł��B

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

		void Spawn(); //���������
		void StopSpawn();//��������Ȃ�
	};

}
