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
		// ���˂�������ɔ�������̂�h�����߃I�[�i�[�𔻒肩�珜�O
		collComp->AddExcludeCollisionGameObject(m_owner.lock());
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
		SoundManager::GetInstance()->Play(L"ExplosionSE", 0, 0.1f);

		// �����̏���

		if (other->FindTag(L"Break")) {
			auto breakBlock = dynamic_pointer_cast<BreakBlock>(other);
			breakBlock->BlockDamage(10);
		}
		else {
			const auto& players = PlayerManager::GetInstance()->GetAllPlayer();
			for (auto player : players) {
				auto pos = player->GetTransform()->GetPosition();
				auto myPos = GetTransform()->GetPosition();
				auto distance = (pos - myPos).length();
				// �������a���ɂ���ꍇ�m�b�N�o�b�N
				if (distance <= m_maxRadius) {
					auto rate = 1.0f;
					// �ŏ�������艓���ꍇ
					if (distance > m_minimumRadius) {
						// ���e��苗������������ƈЗ͂����炷�悤�ɂ���
						rate = 1 - ((distance - m_minimumRadius) / (m_maxRadius - m_minimumRadius));
					}
					KnockBackData data(
						KnockBackData::Category::Bomb,
						pos - myPos, m_power * rate, m_owner
					);
					// �m�b�N�o�b�N
					player->KnockBack(data);
				}
			}
		}
		// ���g���폜
		Destroy<Bomb>();
	}
}