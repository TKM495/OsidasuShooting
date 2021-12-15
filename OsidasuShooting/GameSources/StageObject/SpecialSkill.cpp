/*!
@file   SpecialLaser.cpp
@brief  �K�E�Z�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SpecialLaser::OnCreate() {
		// �����蔻��̒ǉ�
		auto PtrColl = AddComponent<CollisionObb>();
		// �Փˉ����𖳎�
		PtrColl->SetAfterCollision(AfterCollision::None);
		PtrColl->SetDrawActive(true);

		// �ʒu�̒���
		GetTransform()->SetPivot(0, 0, -m_zPosSet);

		// ���˕����ɐ��ʂ�������
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = rad;

		auto ownerPos = m_owner->GetTransform()->GetPosition();
		m_transformData.Position.z += m_zPosSet;

		//m_transformData.Position = m_direction.normalize() * -m_zPosSet;
		// �����̒ǉ�
		AddComponent<LifeSpan>(m_lifeSpan);

		ApplyTransform();

		// �G�t�F�N�g�̓I�u�W�F�N�g�̈ʒu�̉e�����󂯂邽�߃Z�b�g�A�b�v�̂���
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

	// ����m�F�p�̊֐�
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

		// �ʒu�𓯊�
		//GetComponent<EfkComponent>()->SyncPosition();
	}

	void SpecialLaser::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player") || other->FindTag(L"Bullet")) return;
	}
}