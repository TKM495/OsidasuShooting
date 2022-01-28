/*!
@file   Bomb.cpp
@brief  爆弾クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Bomb::Bomb(const shared_ptr<Stage>& stage,
		const shared_ptr<PlayerBase>& owner,
		const PredictionLine& predictionLine,
		const Vec3& startPoint,
		const Vec3& endPoint,
		float power)
		:AdvancedGameObject(stage), m_owner(owner),
		m_predictionLine(predictionLine),
		m_delta(0.0f), m_startPoint(startPoint), m_endPoint(endPoint),
		m_timeRate(2.0f), m_minimumRadius(4.0f), m_maxRadius(7.0f), m_power(power), m_lifeSpan(5.0f),
		m_isExploded(false)
	{
		m_transformData.Position = m_startPoint;
		m_transformData.Scale = Vec3(0.5f);
	}

	void Bomb::OnCreate() {
		//auto drawComp = AddComponent<PNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE");

		AddComponent<CircleShadow>();

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
		efkComp->IsSyncPosition(L"Bomb", true);
		efkComp->Play(L"Bomb");

		AddTag(L"Bomb");
	}

	void Bomb::OnUpdate() {
		auto timeScale = 1.0f;
		auto gameStage = GetTypeStage<GameStage>(false);
		if (gameStage) {
			timeScale = gameStage->GetTimeScale();
		}

		auto pos = m_predictionLine.ParabolaCalculate(
			m_startPoint, m_endPoint, m_delta * m_timeRate);
		GetTransform()->SetPosition(pos);
		m_delta += App::GetApp()->GetElapsedTime() * timeScale;
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
		SoundManager::GetInstance()->Play(L"ExplosionSE", 0, 0.5f);

		//// プレイヤーに直撃した場合
		//auto player = dynamic_pointer_cast<PlayerBase>(other);
		//if (player) {
		//	auto pos = player->GetTransform()->GetPosition();
		//	auto myPos = GetTransform()->GetPosition();
		//	KnockBackData data(
		//		KnockBackData::Category::Bomb,
		//		pos - myPos, m_power * 2, m_owner
		//	);
		//	// ノックバック
		//	player->KnockBack(data);
		//}

		// 爆風の処理
		auto gameObjects = GetStage()->GetGameObjectVec();
		for (auto obj : gameObjects) {
			// プレイヤーの場合
			auto player = dynamic_pointer_cast<PlayerBase>(obj);
			if (player) {
				auto pos = player->GetTransform()->GetPosition();
				auto myPos = GetTransform()->GetPosition();
				auto distance = (pos - myPos).length();
				auto rate = PowerCalc(distance);
				if (rate > 0) {
					KnockBackData data(
						KnockBackData::Category::Bomb,
						pos - myPos, m_power * rate, m_owner
					);
					// ノックバック
					player->KnockBack(data);
				}
			}

			// 壊れるブロックの場合
			auto breakBlock = dynamic_pointer_cast<BreakBlock>(obj);
			if (breakBlock) {
				auto pos = breakBlock->GetTransform()->GetPosition();
				auto myPos = GetTransform()->GetPosition();
				auto distance = (pos - myPos).length();
				auto rate = PowerCalc(distance);
				breakBlock->BlockDamage(rate * 5);
			}

			// アイテムの場合
			auto item = dynamic_pointer_cast<modifiedClass::Item>(obj);
			if (item) {
				auto pos = item->GetComponent<Transform>()->GetPosition();
				auto myPos = GetTransform()->GetPosition();
				auto distance = (pos - myPos).length();
				auto rate = PowerCalc(distance);
				if (rate > 0) {
					item->GetComponent<PhysicalBehavior>()->
						Impact(pos - myPos, m_power * rate);
				}
			}
		}
		// 自身を削除
		Destroy<Bomb>();
	}

	float Bomb::PowerCalc(float distance) {
		float rate = 0.0f;
		// 爆発半径内にいる場合ノックバック
		if (distance <= m_maxRadius) {
			rate = 1.0f;
			// 最小距離より遠い場合
			if (distance > m_minimumRadius) {
				// 爆弾より距離が遠ざかると威力を減らすようにする
				rate = 1 - ((distance - m_minimumRadius) / (m_maxRadius - m_minimumRadius));
			}
		}
		return rate;
	}
}