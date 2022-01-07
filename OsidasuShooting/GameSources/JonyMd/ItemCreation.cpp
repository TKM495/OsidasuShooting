#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ItemCreation::OnCreate()
	{
		YPosition = 10.0f;
		isUniquePosition = false;
		spawnArea = SpawnArea::Block;
	}
	
	void ItemCreation::RandomlySpawn()
	{

		if (areaPositionList.size() < 1)
		{
			SetArea();
		}

		if (spawnScale != Vec3(0, 0, 0) && isUniquePosition && YPosition == 0.0f)
		{
			AdjustingAreaPosition();
		}

		//setting random position
		srand(time(0));
		int index = rand() % areaPositionList.size();
		//setting random position...end


		//spawn on that position
		auto spawn = GetStage()->AddGameObject<Item>();
		spawn->GetComponent<Transform>()->SetPosition(areaPositionList[index]);
		if (spawnScale == Vec3(0, 0, 0))
		{
			spawnScale = spawn->GetComponent<Transform>()->GetScale();
		}
		//spawn on that position...end

		//for the enum class ItemType 
		int totalItems = (int)Item::ItemType::totalItems; //last enum member used as total members
		srand(time(0));
		int randItems = rand() % totalItems;
		spawn->spawnItem = static_cast<Item::ItemType>(randItems); //assigning random value to the enum to set the current enum member
		//for the enum class ItemType ...end




		//changing Shape according enum value
		auto currentItem = spawn->spawnItem;
		auto component = spawn->GetComponent<BcPNTStaticDraw>();

		switch (currentItem)
		{
		case Item::ItemType::Cube:
			component->SetMeshResource(L"DEFAULT_CUBE");
			break;
		case Item::ItemType::Sphere:
			component->SetMeshResource(L"DEFAULT_SPHERE");
		default:
			break;
		}
		//changing Shape according enum value...end



		//for not to repeat purposes
		auto it = areaPositionList.begin();
		auto position = areaPositionList[index];
		while (it != areaPositionList.end()) {
			if (position == *it)
			{
				it = areaPositionList.erase(it); // deleting area which has empty value
			}
			else {
				it++;
			}
		}
		//for not to repeat purposes...end

	}



	void ItemCreation::AdjustingAreaPosition()
	{

		auto objs = GetStage()->GetGameObjectVec();

		for (auto& obj : objs)
		{
			auto it = areaPositionList.begin();
			while (it != areaPositionList.end()) {
				auto position = obj->GetComponent<Transform>()->GetPosition();
				auto relativePosition = *it - position;
				auto distance = relativePosition.length();

				if ((distance <= spawnScale.x + space) || (distance <= spawnScale.z + space))
				{
					it = areaPositionList.erase(it); // deleting area which has empty value
				}
				else {
					it++;
				}
			}
		}

		if (areaPositionList.size() < 1)
		{
			return;
		}

	}

	void ItemCreation::SetArea()
	{
		auto stage = GetStage();
		auto objs = stage->GetGameObjectVec();

		bool isBlockFound = false;

		int srandval = 0;

		Vec3 position;
		Vec3 scale;

		shared_ptr<Block> block;
		shared_ptr<Area> area;
		//Step 2 //Total Step 3, //Current Step is 2, //search for Step 3
		for (auto& obj : objs)
		{
			bool doRandomCal = false;

			switch (spawnArea)
			{
			case SpawnArea::Area:
				area = dynamic_pointer_cast<Area>(obj);
				if (area)
				{
					position = area->GetComponent<Transform>()->GetPosition();
					scale = area->GetComponent<Transform>()->GetScale();
					doRandomCal = true;
				}
				break;
			case SpawnArea::Block:
				block = dynamic_pointer_cast<Block>(obj);
				if (block)
				{
					position = block->GetComponent<Transform>()->GetPosition();
					scale = block->GetComponent<Transform>()->GetScale();
					doRandomCal = true;
				}
				break;

				//Step 3 //Total Step 3, //Current Step is 3, //search for Step 1
			default:
				break;
			}


			if (doRandomCal)
			{
				isBlockFound = true;

				scale /= 2;
				position.y = YPosition;


				for (int i = 0; i < 2; i++)
				{
					float val;
					float min;
					float max;

					if (i == 0)
					{
						val = position.x;
						min = val - scale.x;
						max = val + scale.x;
					}
					else if (i == 1)
					{
						val = position.z;
						min = val - scale.z;
						max = val + scale.z;
					}


					float positiveMin = min;
					float positiveMax = max;

					if (min < 0)
					{
						positiveMin *= -1;
					}
					if (max < 0)
					{
						positiveMax *= -1;
					}


					int lowerVal = (int)positiveMin;
					int higherVal = (int)positiveMax;
					if (lowerVal > higherVal)
					{
						lowerVal = (int)positiveMax;
						higherVal = (int)positiveMin;
					}


					int modulo;
					float adjustVal;


					srand(time(0)); 
					float randval;
					float randDecimal = rand() % 99;
					randDecimal = randDecimal / 100;

					if (min < 0 && max < 0)
					{
						modulo = higherVal - lowerVal;
						adjustVal = (float)lowerVal;
						randval = rand() % modulo + adjustVal;

						randval *= -1;
						randDecimal *= -1;
					}
					else if (min < 0 && max == 0)
					{
						modulo = higherVal;
						randval = rand() % modulo;

						if (randval > 0) {
							randval *= -1;
							randDecimal *= -1;
						}
					}
					else if (min > 0 && max > 0)
					{
						modulo = higherVal - lowerVal;
						adjustVal = (float)lowerVal;
						randval = rand() % modulo + adjustVal;
					}
					else if (min == 0 && max > 0)
					{
						modulo = higherVal;
						randval = rand() % modulo;
					}
					else
					{
						modulo = higherVal;
						if (higherVal == lowerVal) {
							randval = rand() % modulo;


							int randSign = rand() % 2;
							if (randSign == 1) // suppose, Negative Number
							{
								randval *= -1;
							}
						}
						else
						{
							adjustVal = lowerVal;
							randval = rand() % modulo + adjustVal;
							randval = min + randval;
						}

					}
					randval += randDecimal;

					if (i == 0)
					{
						position.x = randval;
					}
					else if (i == 1)
					{
						position.z = randval;
					}

				}

				areaPositionList.push_back(position);
			}
		}

		if (!isBlockFound)
		{
			return;
		}
	}


}