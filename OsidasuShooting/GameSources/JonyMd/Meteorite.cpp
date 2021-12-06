#include "stdafx.h"
#include "Project.h"
#include <time.h>

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

		scale.x = 1;//�������Ă��������B�B�B�B�Bwarning
		scale.y = 1;//�������Ă��������B�B�B�B�Bwarning
		scale.z = 1;//�������Ă��������B�B�B�B�Bwarning
		spawnScale = scale / 2; //���̃T�C�Y


		position.x = 0;//�ꎞ�I��
		position.y = 16;//�Œ�
		position.z = 0;//�ꎞ�I��
		transform->SetScale(scale);
		transform->SetPosition(Vec3(0,16,0));//�ꎞ�I��
		


		CreatingRandomPosition();//�����_���ɂ��Ƃ����W�擾���邽��

	}


	void Meteorite::CreatingRandomPosition()
	{
		//�擾����
		float minPosX = -12.375; //stage1.csv �t�@�C���́@�ʏ�@�Œ�X���W
		float maxPosX = 12.375;//stage1.csv �t�@�C���́@�ʏ�@�ő�X���W

		float minPosZ = -15.125;//stage1.csv �t�@�C���́@�ʏ�@�Œ�Z���W
		float maxPosZ = 6.87;//stage1.csv �t�@�C���́@�ʏ�@�ő�Z���W
		//�擾����B�B�B�I


		//�擾�����l��������
		minPosX = (minPosX + spawnScale.x);
		maxPosX = maxPosX - spawnScale.x;

		minPosZ = minPosZ + spawnScale.z;
		maxPosZ = maxPosZ - spawnScale.z;
		//�擾�����l��������B�B�B�I

		//position �̔z������
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
		//position �̔z������B�B�B�I


		//�����_���̕��@
		random_shuffle(spawnArea.begin(), spawnArea.end());

		GetComponent<Transform>()->SetPosition(spawnArea[0]);
		//�����_���̕��@�B�B�B�I
	}//CreatingRandomPosition�B�B�B�I


	void Meteorite::OnCollisionEnter(shared_ptr<GameObject>& other) {

		bool beDestroyed = true;//stage1.csv �t�@�C���́@�ʏ�@Block ... ����Block��other�����A�m�F���邽��
		auto stage = GetStage();
		auto objs = stage->GetGameObjectVec();

		//Block��other�����A�m�F���邽��
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
		//Block��other�����A�m�F���邽�߁B�B�B�I


		if (beDestroyed == true)
		{
			GetStage()->RemoveGameObject<Meteorite>(GetThis<Meteorite>());
		}
	}//OnCollisionEnter�B�B�B�I

}
