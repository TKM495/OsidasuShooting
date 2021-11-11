#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Bullet::OnCreate()
	{
		auto PtrColl = AddComponent<CollisionSphere>();
		//PtrColl->SetDrawActive(true);
		PtrColl->SetAfterCollision(AfterCollision::None);

		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = XMConvertToDegrees(rad);

		ObjectSetUp();

		// エフェクトはオブジェクトの位置の影響を受けるためセットアップのあと
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet");
		efkComp->SetScale(m_transformData.Scale);
		efkComp->SetRotation(m_transformData.Rotation);
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