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

		// ���˕����ɐ��ʂ�������
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = rad;

		// �ʒu�̒���
		m_transformData.Position.z = m_zPosSet;

		//m_transformData.Position = m_direction.normalize() * -m_zPosSet;
		// �����̒ǉ�
		//AddComponent<LifeSpan>(m_lifeSpan);

		ObjectSetUp();

		//// �G�t�F�N�g�̓I�u�W�F�N�g�̈ʒu�̉e�����󂯂邽�߃Z�b�g�A�b�v�̂���
		//auto efkComp = AddComponent<EfkComponent>();
		//efkComp->SetEffectResource(L"Bullet");
		//efkComp->SetScale(m_transformData.Scale);
		//efkComp->SetRotation(m_transformData.Rotation);
		//efkComp->Play();

		AddTag(L"Bullet");

		Debug::GetInstance()->Log(Utility::ConvertRadVecToDegVec(
			GetComponent<Transform>()->GetRotation()));
		Debug::GetInstance()->Log(GetComponent<Transform>()->GetRotation());
		Debug::GetInstance()->Log(GetComponent<Transform>()->GetPivot());
		Debug::GetInstance()->Log(GetComponent<Transform>()->GetWorldPosition());
		Debug::GetInstance()->Log(m_transformData.Position);

		//GetComponent<Transform>()->SetWorldPosition(Vec3(0));
	}

	void SpecialLaser::OnUpdate() {

		auto transPos = GetTransform()->GetPosition(); //(x,y,z)
		float deltaTime = App::GetApp()->GetElapsedTime();

		// �ʒu�𓯊�
		//GetComponent<EfkComponent>()->SyncPosition();
	}

	void SpecialLaser::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player") || other->FindTag(L"Bullet")) return;
	}
}