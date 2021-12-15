/*!
@file   SpecialLaser.cpp
@brief  必殺技の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SpecialLaser::OnCreate() {
		// 当たり判定の追加
		auto PtrColl = AddComponent<CollisionObb>();
		// 衝突応答を無視
		PtrColl->SetAfterCollision(AfterCollision::None);
		PtrColl->SetDrawActive(true);

		// 位置の調整
		GetTransform()->SetPivot(0, 0, -m_zPosSet);

		// 発射方向に正面を向ける
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = rad;

		auto ownerPos = m_owner->GetTransform()->GetPosition();
		m_transformData.Position.z += m_zPosSet;

		//m_transformData.Position = m_direction.normalize() * -m_zPosSet;
		// 寿命の追加
		AddComponent<LifeSpan>(m_lifeSpan);

		ApplyTransform();

		// エフェクトはオブジェクトの位置の影響を受けるためセットアップのあと
		auto transData = m_transformData;
		transData.Position = m_owner->GetTransform()->GetPosition();
		transData.Rotation = Utility::ConvertRadVecToDegVec(transData.Rotation);
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetCoordinateType(CoordinateType::Absolute);
		efkComp->SetEffectResource(L"Laser", transData);
		efkComp->Play(L"Laser");

		Debug::GetInstance()->Log(transData.Position);
		Debug::GetInstance()->Log(transData.Scale);
		Debug::GetInstance()->Log(transData.Rotation);

		AddTag(L"Laser");

		//Debug::GetInstance()->Log(Utility::ConvertRadVecToDegVec(
		//	GetComponent<Transform>()->GetRotation()));
		//Debug::GetInstance()->Log(GetComponent<Transform>()->GetRotation());
		//Debug::GetInstance()->Log(GetComponent<Transform>()->GetPivot());
		//Debug::GetInstance()->Log(GetComponent<Transform>()->GetWorldPosition());
		//Debug::GetInstance()->Log(m_transformData.Position);

		//GetComponent<Transform>()->SetWorldPosition(Vec3(0));
	}

	// 動作確認用の関数
	void SpecialLaser::MoveTestLaser() {
		auto trans = GetTransform(); //(x,y,z)

		auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ctrlX = 0.0f;
		auto ctrlY = 0.0f;
		if (ctrlVec[0].bConnected) {
			ctrlX = ctrlVec[0].fThumbRX;
			ctrlY = ctrlVec[0].fThumbRY;
		}
		if (ctrlX != 0 || ctrlY != 0) {
			auto rad = atan2f(-ctrlY, ctrlX) + XM_PIDIV2;
			trans->SetRotation(0, rad, 0);
		}
		auto ownerPos = m_owner->GetTransform()->GetPosition();
		ownerPos.z += m_zPosSet;
		trans->SetPosition(ownerPos);
	}

	void SpecialLaser::OnUpdate() {
		//MoveTestLaser();

		//auto transPos = GetTransform()->GetPosition(); //(x,y,z)
		//float deltaTime = App::GetApp()->GetElapsedTime();

		// 位置を同期
		//GetComponent<EfkComponent>()->SyncPosition();
	}

	void SpecialLaser::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player") || other->FindTag(L"Bullet")) return;
	}
}