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
		// 発射した直後に爆発するのを防ぐためPlayerも判定から除外する
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
		// 一回のみ実行
		if (m_isExploded)
			return;
		m_isExploded = true;
		// 爆弾によるノックバック処理
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"Bomb");
		// プレイヤーの取得
		const auto& players = PlayerManager::GetInstance()->GetAllPlayer();
		for (auto player : players) {
			auto pos = player->GetTransform()->GetPosition();
			auto myPos = GetTransform()->GetPosition();
			auto distance = (pos - myPos).length();
			// 爆発半径内にいる場合ノックバック
			if (distance < m_radius) {
				PlayerBase::KnockBackData data(
					PlayerBase::KnockBackData::Category::Bomb,
					pos - myPos, m_power, m_owner
				);
				// ノックバック
				player->KnockBack(data);
			}
		}
		// 自身を削除
		Destroy<Bomb>();
	}
}