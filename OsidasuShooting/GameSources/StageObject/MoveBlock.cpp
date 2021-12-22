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
		const TransformData transformData,
		const wstring& line
	) :
		Block(stage, transformData)
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

	void MoveBlock::MovingBlock() {
		// �f���^�^�C���擾
		const auto& app = App::GetApp();
		const auto delta = app->GetElapsedTime();

		// ���݂̃|�W�V����
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();

		auto rootMoving = m_moveRoot * delta * 0.1f;// �ړ�


		if (!m_isWait) {
			if (m_startPosition.x >= m_markPosition.x) {// m_startPos�̕����傫���ꍇ
				if (pos.x > m_startPosition.x ||
					pos.x < m_markPosition.x) {
					m_isWait = true;
					m_waitTime = 0;
					if (m_isReturnBlock) m_isReturnBlock = false;
					else m_isReturnBlock = true;

					if (pos.x > m_startPosition.x) ptrTrans->SetPosition(m_startPosition);
					else if (pos.x < m_markPosition.x) ptrTrans->SetPosition(m_markPosition);
				}
			}
			else {										// m_startPos�̕����������ꍇ
				if (pos.x < m_startPosition.x ||
					pos.x > m_markPosition.x) {
					m_isWait = true;
					m_waitTime = 0;
					if (m_isReturnBlock) m_isReturnBlock = false;
					else m_isReturnBlock = true;

					if (pos.x < m_startPosition.x) ptrTrans->SetPosition(m_startPosition);
					else if (pos.x > m_markPosition.x) ptrTrans->SetPosition(m_markPosition);
				}
			}
			if (m_isReturnBlock) pos -= rootMoving;
			else pos += rootMoving;

			if(!m_isWait) ptrTrans->SetPosition(pos);
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
		if (!m_isSetUp) {
			//	SetUpAnimation();
		}
		else {
			auto ptrColl = GetComponent<CollisionObb>();
			ptrColl->SetAfterCollision(AfterCollision::Auto);
		}

		m_isSetUp = true;
		MovingBlock();
	}

	void MoveBlock::SetUpAnimation() {
		auto pos = GetTransform()->GetPosition();
		if (pos.y < m_setPosition.y) {
			pos.y = m_setPosition.y;

			m_isSetUp = true;
		}
		else {
			if (pos.y > m_setPosition.y - 0.5f) {
				pos = m_setPosition;
			}
			else {
				auto movePosY = (m_setPosition.y - pos.y) * 0.5f;
				pos.y = movePosY;
			}
		}
		GetTransform()->SetPosition(pos);
	}

}