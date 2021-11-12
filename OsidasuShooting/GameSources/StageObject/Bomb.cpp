/*!
@file   Bomb.cpp
@brief  ���e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Bomb::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_CUBE");

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetAfterCollision(AfterCollision::None);

		AddComponent<LifeSpan>(m_lifeSpan);

		ObjectSetUp();

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Explosion");

		AddTag(L"Bomb");
	}

	void Bomb::OnUpdate() {
		auto pos = m_predictionLine.ParabolaCalculate(
			m_startPoint, m_endPoint, m_delta * m_timeRate);
		GetTransform()->SetPosition(pos);
		m_delta += App::GetApp()->GetElapsedTime();
	}

	void Bomb::OnCollisionEnter(shared_ptr<GameObject>& other) {
		// ���˂�������ɔ�������̂�h������Player������ɉ�����
		if (other->FindTag(L"Player") ||
			other->FindTag(L"Bullet") ||
			other->FindTag(L"Bomb") ||
			m_isExploded)
			return;
		m_isExploded = true;
		// ���e�ɂ��m�b�N�o�b�N�����i�{����Player���Ɏ�������j
		GetComponent<EfkComponent>()->Play();
		auto objs = GetStage()->GetGameObjectVec();
		for (auto obj : objs) {
			auto ptr = dynamic_pointer_cast<Player>(obj);
			if (ptr) {
				auto pos = ptr->GetTransform()->GetPosition();
				auto myPos = GetTransform()->GetPosition();
				auto distance = (pos - myPos).length();
				if (distance < m_radius) {
					ptr->KnockBack(pos - myPos, m_power);
				}
			}
		}
		GetStage()->RemoveGameObject<Bomb>(GetThis<Bomb>());
	}
}