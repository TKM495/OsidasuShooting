#pragma once
#include "stdafx.h"

namespace basecross {
	namespace modifiedClass {
		class ItemCreation : public GameObject
		{
			//Where to Spawn
			vector<Vec3> areaPositionList;

			//Which to Spawn
			Vec3 spawnScale;
			float YPosition; //YPosition = 0.0f is just above the area position, positive value is upper positionand negative value is lower position .

			//For Unique Position
			bool isUniquePosition; // true (if other GameObject is on that position will not spawn)
			float space = 0.1;//space between 2 objects // 0 there is no space //Need when UniquePosition is true;

			void SetArea();//Getting a list of position where to Spawn

			//if there is already a object in AreaPosition, position will be adjusted
			void AdjustingAreaPosition();

			enum class SpawnArea {//Step 1 //Total Step 3, //Current Step is 1, //search for Step 2
				Area,
				Block
			};
			SpawnArea spawnArea;

		public:
			ItemCreation(const shared_ptr<Stage>& stage)
				:GameObject(stage)
			{}

			void OnCreate() override;

			//Y position is fixed, X and Z position will be calculated by Randomly. isUniquePosition = if other GameObject is on that position will not spawn
			void RandomlySpawn();

			//Set a Value for Y Position
			void SetYposition(float number)
			{
				YPosition = number;
				isUniquePosition = false;
			}

			void SetUniquePosition(bool value)
			{
				isUniquePosition = value;
				if (value) {
					YPosition = 0.0f;
				}
				else
				{
					YPosition = 20.0f; //Default
				}
			}
		};
	}
}