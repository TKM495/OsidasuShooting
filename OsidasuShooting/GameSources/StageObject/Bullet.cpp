/*!
@file   Bullet.cpp
@brief  �e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Bullet::OnCreate()
	{
		// �����蔻��̒ǉ�
		auto PtrColl = AddComponent<CollisionSphere>();
		// �Փˉ����𖳎�
		PtrColl->SetAfterCollision(AfterCollision::None);
		// �I�[�i�[�ƒe�Ƃ̓����蔻��𖳎�
		PtrColl->AddExcludeCollisionGameObject(m_owner.lock());
		PtrColl->AddExcludeCollisionTag(L"Bullet");

		// ���˕����ɐ��ʂ�������
		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		m_transformData.Rotation.y = XMConvertToDegrees(rad);

		// �����̒ǉ�
		AddComponent<LifeSpan>(m_lifeSpan);

		// �G�t�F�N�g
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet");
		efkComp->SetScale(m_transformData.Scale);
		efkComp->SetRotation(m_transformData.Rotation);
		efkComp->Play();

		// �e
		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_SPHERE");

		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate()
	{
		auto transPos = GetTransform()->GetPosition(); //(x,y,z)

		float deltaTime = App::GetApp()->GetElapsedTime();

		transPos += m_direction.normalize() * m_speed * deltaTime;
		GetTransform()->SetPosition(transPos);

		// �ʒu�𓯊�
		GetComponent<EfkComponent>()->SyncPosition();
	}

	void Bullet::OnDestroy() {
		// �I�u�W�F�N�g�폜���ɃG�t�F�N�g����~
		GetComponent<EfkComponent>()->Stop();
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto ptr = dynamic_pointer_cast<PlayerBase>(other);
		if (ptr) {
			PlayerBase::KnockBackData data(
				PlayerBase::KnockBackData::Category::Bullet,
				m_direction, m_knockBackAmount, m_owner
			);
			// �m�b�N�o�b�N
			ptr->KnockBack(data);
		}
		// ���g���폜
		Destroy<Bullet>();
	}
}
//end basecross