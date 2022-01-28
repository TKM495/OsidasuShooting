#pragma once
#include "stdafx.h"

namespace basecross {

	class ItemCreation : public GameObject
	{
		vector<Vec3> areaPositionList;
		Vec3 targetScale;

		float positionX;
		float positionY;
		float positionZ;

		bool isRandPosX;
		bool isRandPosY;
		bool isRandPosZ;

		void CreatePositionLists();
		Vec3 CheckingRotation(Vec3 scale,Vec3 rotation);

	public:
		ItemCreation(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		
		void SpawnInRandPosition();


	};
}
