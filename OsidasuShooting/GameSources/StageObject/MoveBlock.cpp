/*!
@file   MoveBlock.cpp
@brief	���t���N�^�[�u���b�N�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "Bullet.h"

namespace basecross {
	MoveBlock::MoveBlock(
		const shared_ptr<Stage>& stage,
		const wstring& line
	) :
		AdvancedGameObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_transformData.Position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_transformData.Scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_transformData.Rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
		// �����n�_
		m_markPosition = Vec3(
			(float)_wtof(tokens[11].c_str()),
			(float)_wtof(tokens[12].c_str()),
			(float)_wtof(tokens[13].c_str())
		);
	}

	void MoveBlock::OnCreate() {
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		// �u���b�N�Ƃ̓����蔻��𖳎�
		ptrColl->AddExcludeCollisionTag(L"Block");
		ptrColl->SetFixed(true);

		auto ptrTrans = GetTransform();
		m_startPosition = ptrTrans->GetPosition();

		m_moveRoot = m_startPosition - m_markPosition; // �����̎擾
		m_waitTime = 0;
		m_isWait = true;

		//// �{���̈���ɐݒu
		//m_setPosition = GetTransform()->GetPosition();
		//auto setPos = m_setPosition;
		//setPos.y = -1;
		//GetTransform()->SetPosition(setPos);
		//ApplyTransform();

		AddTag(L"Block");
	}

	void MoveBlock::MoveSwitch() {
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();

	}

	void MoveBlock::MovingBlock() {
		// �f���^�^�C���擾
		const auto& app = App::GetApp();
		const auto delta = app->GetElapsedTime();

		// ���݂̃|�W�V����
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();

		Easing<Vec3> easing;

		//auto rootMoving = m_moveRoot * delta * 0.1f;// �ړ�

		if (!m_isWait) {
			m_totalTime += delta;
			if (m_totalTime >= 4.0f) {
				m_totalTime = 0;
				m_isWait = true;
				m_waitTime = 0;

				if (m_isGotoMarkPos) m_isGotoMarkPos = false;
				else m_isGotoMarkPos = true;
			}
			Vec3 rootMoving;
			if (!m_isGotoMarkPos)
				rootMoving = easing.EaseInOut(
					EasingType::Quadratic, m_startPosition, m_markPosition, m_totalTime, 4.0f);
			else
				rootMoving = easing.EaseInOut(
					EasingType::Quadratic, m_markPosition, m_startPosition, m_totalTime, 4.0f);

			ptrTrans->SetPosition(rootMoving);
		}
		else {
			if (m_waitTime > 1) {
				m_isWait = false;
			}
			else {
				m_waitTime += delta;
			}
		}
	}

	void MoveBlock::OnUpdate() {
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		MovingBlock();
	}
}