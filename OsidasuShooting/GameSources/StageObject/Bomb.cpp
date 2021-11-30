/*!
@file   Bomb.cpp
@brief  ���e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Bomb::OnCreate() {
		//auto drawComp = AddComponent<PNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetAfterCollision(AfterCollision::None);
		// ���˂�������ɔ�������̂�h������Player�����肩�珜�O����
		collComp->AddExcludeCollisionTag(L"Player");
		collComp->AddExcludeCollisionTag(L"Bullet");
		collComp->AddExcludeCollisionTag(L"Bomb");

		AddComponent<LifeSpan>(m_lifeSpan);

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Explosion");
		efkComp->SetEffectResource(L"Bomb");
		efkComp->Play(L"Bomb");

		AddTag(L"Bomb");
	}

	void Bomb::OnUpdate() {
		auto pos = m_predictionLine.ParabolaCalculate(
			m_startPoint, m_endPoint, m_delta * m_timeRate);
		GetTransform()->SetPosition(pos);
		m_delta += App::GetApp()->GetElapsedTime();
		GetComponent<EfkComponent>()->SyncPosition(L"Bomb");
	}

	void Bomb::OnDestroy() {
		GetComponent<EfkComponent>()->Stop(L"Bomb");
	}

	void Bomb::OnCollisionEnter(shared_ptr<GameObject>& other) {
		// ���̂ݎ��s
		if (m_isExploded)
			return;
		m_isExploded = true;
		// ���e�ɂ��m�b�N�o�b�N����
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"Bomb");
		// �v���C���[�̎擾
		const auto& players = PlayerManager::GetInstance()->GetAllPlayer();
		for (auto player : players) {
			auto pos = player->GetTransform()->GetPosition();
			auto myPos = GetTransform()->GetPosition();
			auto distance = (pos - myPos).length();
			// �������a���ɂ���ꍇ�m�b�N�o�b�N
			if (distance < m_radius) {
				PlayerBase::KnockBackData data(
					PlayerBase::KnockBackData::Category::Bomb,
					pos - myPos, m_power, m_owner
				);
				// �m�b�N�o�b�N
				player->KnockBack(data);
			}
		}
		// ���g���폜
		Destroy<Bomb>();
	}
}