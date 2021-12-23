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
		auto effectTrans = m_transformData;
		effectTrans.Position = Vec3(0.0f);
		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet", effectTrans);
		efkComp->SetEffectResource(L"Hit", effectTrans);
		efkComp->Play(L"Bullet");

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
		GetComponent<EfkComponent>()->SyncPosition(L"Bullet");
	}

	void Bullet::OnDestroy() {
		// �I�u�W�F�N�g�폜���ɒe�̃G�t�F�N�g���~���A
		// �q�b�g���̃G�t�F�N�g���Đ�
		auto efkComp = GetComponent<EfkComponent>();
		efkComp->Stop(L"Bullet");
		efkComp->Play(L"Hit");
	}


	void Bullet::Reflect(shared_ptr<GameObject>& reflect) {
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();
		auto rot = ptrTrans->GetRotation();

		auto blockTrans = reflect->GetComponent<Transform>();
		auto blockPos = blockTrans->GetPosition();
		auto blockScl = blockTrans->GetScale();
		auto blockHalfSize = 0.4f;

		auto ptrEfk = GetComponent<EfkComponent>();

		auto reverse = -1;

		// �S�������]

		auto brockSizeX = blockHalfSize * blockScl.x;
		auto brockSizeZ = blockHalfSize * blockScl.z;

		// ���������]
		if (pos.x >= blockPos.x + brockSizeX ||
			pos.x <= blockPos.x - brockSizeX) {
			m_direction.x *= reverse;
		}

		// �c�������]
		if (pos.z >= blockPos.z + brockSizeZ ||
			pos.z <= blockPos.z - brockSizeZ) {
			m_direction.z *= reverse;
		}

		auto rad = atan2f(-m_direction.z, m_direction.x) + XM_PIDIV2;
		rot.y = rad;

		ptrEfk->SetRotation(L"Bullet", rot);
		ptrTrans->SetRotation(rot);

	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Reflector")) {
			Reflect(other);
		}
		else {
			if (other->FindTag(L"Break")) {
				auto breakBlock = dynamic_pointer_cast<BreakBlock>(other);
				breakBlock->BlockDamage(1);

			}
			else {
				auto ptr = dynamic_pointer_cast<PlayerBase>(other);
				if (ptr) {
					KnockBackData data(
						KnockBackData::Category::Bullet,
						m_direction, m_knockBackAmount, m_owner
					);
					// �m�b�N�o�b�N
					ptr->KnockBack(data);
					m_owner.lock()->AddEnergy(5.0f);
				}
			}
			// ���g���폜
			Destroy<Bullet>();
		}
	}
}
//end basecross