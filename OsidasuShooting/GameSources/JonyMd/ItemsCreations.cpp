#include "stdafx.h"
#include "Project.h"

#include <ctime>


namespace basecross {

	void ItemsCreations::OnCreate()
	{
		SetUpdateActive(true);
		time = 0.1f;
		countDown = time;

		SetSpawnScale();//生成されるゲームオブジェクトのScaleを取得する
	}

	void ItemsCreations::OnUpdate()
	{
		if (countDown > 0)
		{
			auto& app = App::GetApp();
			auto deltaTime = app->GetElapsedTime();
			countDown -= deltaTime;
		}
		else
		{
			AreaPosition();
			AdjustingAreaPosition();//remove the position if other GameObject exists
			SpawnInRandomPosition();
			countDown = time;
		}
	}


	void ItemsCreations::Spawn()
	{
		SetUpdateActive(true);
	}

	void ItemsCreations::StopSpawn()
	{
		SetUpdateActive(false);
	}



	void ItemsCreations::AreaPosition()
	{

		auto area = GetStage()->GetSharedGameObject<Area>(L"Area");
		Vec3 areaPos = area->GetComponent<Transform>()->GetPosition();
		Vec3 areaScale = area->GetComponent<Transform>()->GetScale();
		areaScale /= 2; //getting original size


		float minXPosition = (areaPos.x - areaScale.x + spawnScale.x);
		float maxXPosition = areaPos.x + areaScale.x - spawnScale.x;

		float minZPosition = areaPos.z - areaScale.z + spawnScale.z;
		float maxZPosition = areaPos.z + areaScale.z - spawnScale.z;

		float YPosition = areaPos.y + areaScale.y + spawnScale.y;

		srand(std::time(0));

		vector<float> XPosition;
		vector<float> ZPosition;

		for (float i = minXPosition; i <= maxXPosition; i += 0.1f)
		{
			XPosition.push_back(i);
		}

		for (float i = minZPosition; i <= maxZPosition; i += 0.1f)
		{
			ZPosition.push_back(i);
		}


		if (areaPosition.size() > 0) {
			areaPosition.clear();
		}

		for (int i = 0; i < XPosition.size(); i++)
		{
			for (int j = 0; j < ZPosition.size(); j++)
			{
				areaPosition.push_back(Vec3(XPosition[i], YPosition, ZPosition[j]));
			}
		}

	}


	void ItemsCreations::AdjustingAreaPosition()
	{
		auto objs = GetStage()->GetGameObjectVec();

		for (auto& obj : objs)
		{
			auto items = dynamic_pointer_cast<Items>(obj);
			if (items)
			{
				auto it = areaPosition.begin();
				while (it != areaPosition.end()) {
					auto relativePosition = *it - items->AddComponent<Transform>()->GetPosition();
					auto distance = relativePosition.length();

					/*
					* 2や２以下の値で空白が無くなります
					*/
					if ((distance <= spawnScale.x * 2.1) || (distance <= spawnScale.z * 2.1))
					{
						it = areaPosition.erase(it); // deleting area which has empty value
					}
					else {
						it++;
					}
				}
			}
		}

	}


	void ItemsCreations::SpawnInRandomPosition()
	{
		if (areaPosition.size() > 0) {
			Debug::GetInstance()->Log(Util::IntToWStr(areaPosition.size()));

			random_shuffle(areaPosition.begin(), areaPosition.end());

			auto spawn = GetStage()->AddGameObject<Items>();
			spawn->GetComponent<Transform>()->SetPosition(areaPosition[0]);
		}
		else
		{
			Debug::GetInstance()->Log(L"No Place to Spawn");
		}
	}

	void ItemsCreations::SetSpawnScale() {
		auto spawn = GetStage()->AddGameObject<Items>();
		Vec3 spawnPos = spawn->GetComponent<Transform>()->GetPosition();
		spawnScale = spawn->GetComponent<Transform>()->GetScale();
		spawnScale /= 2; //getting original size		
		GetStage()->RemoveGameObject<Items>(spawn);
	}

}