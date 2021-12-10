#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Meteorite::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		auto transform = GetComponent<Transform>(); 
		auto gravity = AddComponent<Gravity>();
		auto collision = AddComponent<CollisionSphere>();


		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		auto scale = transform->GetScale();
		auto position = transform->GetPosition();

		scale.x = 1;//調整してください。。。。。warning
		scale.y = 1;//調整してください。。。。。warning
		scale.z = 1;//調整してください。。。。。warning
		spawnScale = scale / 2; //元のサイズ


		position.x = 0;//一時的に
		position.y = 16;//固定
		position.z = 0;//一時的に
		transform->SetScale(scale);
		transform->SetPosition(Vec3(0,16,0));//一時的に
		


		CreatingRandomPosition();//ランダムにｘとｚ座標取得するため

		ShackCamera();
	}


	void Meteorite::CreatingRandomPosition()
	{
		//取得する
		float minPosX = -12.375; //stage1.csv ファイルの　通常　最低X座標
		float maxPosX = 12.375;//stage1.csv ファイルの　通常　最大X座標

		float minPosZ = -15.125;//stage1.csv ファイルの　通常　最低Z座標
		float maxPosZ = 6.87;//stage1.csv ファイルの　通常　最大Z座標
		//取得する。。。終


		//取得した値調整する
		minPosX = (minPosX + spawnScale.x);
		maxPosX = maxPosX - spawnScale.x;

		minPosZ = minPosZ + spawnScale.z;
		maxPosZ = maxPosZ - spawnScale.z;
		//取得した値調整する。。。終

		//position の配列を作る
		vector<float> XPosition;
		vector<float> ZPosition;
		float YPosition = GetComponent<Transform>()->GetPosition().y;

		for (float i = minPosX; i <= maxPosX; i += 0.1f)
		{
			XPosition.push_back(i);
		}

		for (float i = minPosZ; i <= maxPosZ; i += 0.1f)
		{
			ZPosition.push_back(i);
		}

		if (spawnArea.size() > 0) {
			spawnArea.clear();
		}


		for (int i = 0; i < XPosition.size(); i++)
		{
			for (int j = 0; j < ZPosition.size(); j++)
			{
				spawnArea.push_back(Vec3(XPosition[i], YPosition, ZPosition[j]));
			}
		}
		//position の配列を作る。。。終


		//ランダムの方法
		random_shuffle(spawnArea.begin(), spawnArea.end());

		GetComponent<Transform>()->SetPosition(spawnArea[0]);
		//ランダムの方法。。。終
	}//CreatingRandomPosition。。。終


	void Meteorite::OnCollisionEnter(shared_ptr<GameObject>& other) {

		bool beDestroyed = true;//stage1.csv ファイルの　通常　Block ... もしBlockはotherだか、確認するため
		auto stage = GetStage();
		auto objs = stage->GetGameObjectVec();

		//Blockはotherだか、確認するため
		for (auto& obj : objs)
		{
			auto block = dynamic_pointer_cast<Block>(obj);
			

			if (block==other)
			{
				beDestroyed = false;
				break;
			}
			else
			{
				beDestroyed = true;
			}
		}
		//Blockはotherだか、確認するため。。。終


		if (beDestroyed == true)
		{
			GetStage()->RemoveGameObject<Meteorite>(GetThis<Meteorite>());
		}
	}//OnCollisionEnter。。。終
	

	void Meteorite::OnUpdate()
	{

	}

	void Meteorite::ShackCamera()
	{
		auto stage = GetStage();
		auto cameraSelect = stage->GetView()->GetTargetCamera();

		auto camera = dynamic_pointer_cast<Camera>(cameraSelect);

		shared_ptr<MeteoriteCreation> meteoriteCreation;

		auto objs = stage->GetGameObjectVec();
		//if there is any other ShackingCamera, they will be destroyed
		for (auto& obj : objs)
		{
			auto shackingCamera = dynamic_pointer_cast<ShackingCamera>(obj);

			if(shackingCamera)
			{
				GetStage()->RemoveGameObject<ShackingCamera>(shackingCamera);
			}

		}
		//if there is any other ShackingCamera, they will be destroyed...end


		for (auto& obj : objs)
		{
			meteoriteCreation = dynamic_pointer_cast<MeteoriteCreation>(obj);

			if (meteoriteCreation)
			{
				break;
			}
		}

		if(camera&&meteoriteCreation)
		{
			camera->SetEye(meteoriteCreation->GetCameraEye());
			camera->SetAt(meteoriteCreation->GetCameraAt());
		}

		GetStage()->AddGameObject<ShackingCamera>(); // create new ShackingCamera...end
	}
}
