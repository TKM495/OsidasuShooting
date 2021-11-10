#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Bullet::OnCreate()
	{
		//auto drawComp = AddComponent <BcPNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrColl = AddComponent<CollisionSphere>();
		//PtrColl->SetDrawActive(true);
		PtrColl->SetAfterCollision(AfterCollision::None);

		ObjectSetUp();

		// �G�t�F�N�g�̓I�u�W�F�N�g�̈ʒu�̉e�����󂯂邽�߃Z�b�g�A�b�v�̂���
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet");
		efkComp->SetScale(m_transformData.Scale);
		efkComp->Play();

		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate()
	{
		auto& app = App::GetApp();

		auto transComp = GetComponent<Transform>();
		auto transPos = transComp->GetPosition(); //(x,y,z)

		float deltaTime = app->GetElapsedTime();

		transPos += m_direction.normalize() * m_speed * deltaTime;

		if (m_lifeSpan > 0)
		{
			m_lifeSpan -= deltaTime;
			transComp->SetPosition(transPos);
		}
		else {
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}

		GetComponent<EfkComponent>()->SyncPosition();
	}

	void Bullet::OnDestroy() {
		GetComponent<EfkComponent>()->Stop();
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player") || other->FindTag(L"Bullet"))
			return;
		GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
	}
}
//end basecross