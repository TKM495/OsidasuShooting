/*!
@file   Bomb.cpp
@brief  爆弾クラスの実体
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
		// 発射した直後に爆発するのを防ぐためオーナーを判定から除外
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
		// 一回のみ実行
		if (m_isExploded)
			return;
		m_isExploded = true;

		// 爆弾によるノックバック処理
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"ExplosionSE", 0, 0.1f);

		// 爆風の処理

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
				// 爆発半径内にいる場合ノックバック
				if (distance <= m_maxRadius) {
					auto rate = 1.0f;
					// 最小距離より遠い場合
					if (distance > m_minimumRadius) {
						// 爆弾より距離が遠ざかると威力を減らすようにする
						rate = 1 - ((distance - m_minimumRadius) / (m_maxRadius - m_minimumRadius));
					}
					KnockBackData data(
						KnockBackData::Category::Bomb,
						pos - myPos, m_power * rate, m_owner
					);
					// ノックバック
					player->KnockBack(data);
				}
			}
		}
		// 自身を削除
		Destroy<Bomb>();
	}
}