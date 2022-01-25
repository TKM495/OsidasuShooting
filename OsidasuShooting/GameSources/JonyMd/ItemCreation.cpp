#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ItemCreation::OnCreate()
	{
		positionX = 0.0f;
		positionY = 10.0f;
		positionZ = 0.0f;

		isRandPosX = true;
		isRandPosY = false;
		isRandPosZ = true;

		auto item = GetStage()->AddGameObject<Item>();
		auto itemTransform = item->GetComponent<Transform>();
		targetScale = itemTransform->GetScale() / 2;

		GetStage()->RemoveGameObject<Item>(item);

	}

	void ItemCreation::SpawnInRandPosition()
	{
		srand(time(NULL));

		if (areaPositionList.size() < 1)
		{
			CreatePositionLists();
		}
		random_shuffle(areaPositionList.begin(), areaPositionList.end());
		int randVal = rand() % areaPositionList.size();

		Vec3 position = areaPositionList[randVal];

		auto item = GetStage()->AddGameObject<Item>();
		auto itemTransform = item->GetComponent<Transform>();
		itemTransform->SetPosition(position);

		areaPositionList.erase(areaPositionList.begin());

	}


	void ItemCreation::CreatePositionLists()
	{
		auto stage = GetStage();

		auto objs = stage->GetGameObjectVec();

		random_shuffle(objs.begin(), objs.end());



		for (auto obj : objs)
		{
			auto blockObj = dynamic_pointer_cast<Block>(obj);
			if (blockObj)
			{
				auto transform = blockObj->GetComponent<Transform>();

				Vec3 position = transform->GetPosition();
				Vec3 scale = transform->GetScale()/2;

				Vec3 rotation = transform->GetBeforeRotation();

				scale = CheckingRotation(scale, rotation);

				Vec3 minPosition = position - scale;
				Vec3 maxPosition = position + scale;

				if (isRandPosX && !isRandPosY && !isRandPosZ)
				{
					for (float x = minPosition.x + targetScale.x; x <= maxPosition.x - targetScale.x; x += 0.7f)
					{
						areaPositionList.push_back(Vec3(x, positionY, positionZ));
					}
				}else if (isRandPosX && isRandPosY && !isRandPosZ)
				{
					for (float x = minPosition.x + targetScale.x; x <= maxPosition.x - targetScale.x; x += 0.7f)
					{
						for (float y = minPosition.y + targetScale.y; y <= maxPosition.y - targetScale.y; y += 0.7f)
						{
							areaPositionList.push_back(Vec3(x, y, positionZ));
						}
					}
				}
				else if (isRandPosX && !isRandPosY && isRandPosZ)
				{
					for (float x = minPosition.x + targetScale.x; x <= maxPosition.x - targetScale.x; x += 0.7f)
					{
						for (float z = minPosition.z + targetScale.z; z <= maxPosition.z - targetScale.z; z += 0.7f)
						{
							areaPositionList.push_back(Vec3(x, positionY, z));
						}
					}
				}
				else if (isRandPosX && isRandPosY && isRandPosZ)
				{
					for (float x = minPosition.x + targetScale.x; x <= maxPosition.x - targetScale.x; x += 0.7f)
					{
						for (float y = minPosition.y + targetScale.y; y <= maxPosition.y - targetScale.y; y += 0.7f)
						{
							for (float z = minPosition.z + targetScale.z; z <= maxPosition.z - targetScale.z; z += 0.7f)
							{
								areaPositionList.push_back(Vec3(x, y, z));
							}

						}
					}
				}else if (!isRandPosX && isRandPosY && !isRandPosZ)
				{
					for (float y = minPosition.y + targetScale.y; y <= maxPosition.y - targetScale.y; y += 0.7f)
					{
						areaPositionList.push_back(Vec3(positionX, y, positionZ));
					}
				}else if (!isRandPosX && !isRandPosY && isRandPosZ)
				{
					for (float z = minPosition.z + targetScale.z; z <= maxPosition.z - targetScale.z; z += 0.7f)
					{
						areaPositionList.push_back(Vec3(positionX, positionY, z));
					}
				}else if (!isRandPosX && isRandPosY && isRandPosZ)
				{
					for (float y = minPosition.y + targetScale.y; y <= maxPosition.y - targetScale.y; y += 0.7f)
					{
						for (float z = minPosition.z + targetScale.z; z <= maxPosition.z - targetScale.z; z += 0.7f)
						{
							areaPositionList.push_back(Vec3(positionX, y, z));
						}

					}
				}

			}
		}

	}//CreateRandomTransforms...end


	Vec3 ItemCreation::CheckingRotation(Vec3 scale, Vec3 rotation)
	{
		if (Util::FloatToWStr(XMConvertToDegrees(rotation.y)) == L"90")
		{
			float tempZ = scale.z;
			scale.z = scale.x;
			scale.x = tempZ;
		}
		return scale;
	}//CheckingRotation...end


}