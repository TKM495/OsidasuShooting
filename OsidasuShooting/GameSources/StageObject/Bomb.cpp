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
		// ���e�ɂ��m�b�N�o�b�N����
		GetComponent<EfkComponent>()->Play();
		auto objs = GetStage()->GetGameObjectVec();
		for (auto obj : objs) {
			auto ptr = dynamic_pointer_cast<PlayerBase>(obj);
			// �v���C���[�̏ꍇ
			if (ptr) {
				auto pos = ptr->GetTransform()->GetPosition();
				auto myPos = GetTransform()->GetPosition();
				auto distance = (pos - myPos).length();
				// �������a���ɂ���ꍇ�m�b�N�o�b�N
				if (distance < m_radius) {
					ptr->KnockBack(pos - myPos, m_power, m_owner.lock());
				}
			}
		}
		GetStage()->RemoveGameObject<Bomb>(GetThis<Bomb>());
	}
}