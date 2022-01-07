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
			(float)_wtof(tokens[10].c_str()),
			(float)_wtof(tokens[11].c_str()),
			(float)_wtof(tokens[12].c_str())
		);
		// �ړ����x
		m_moveSpeed = (float)_wtof(tokens[13].c_str());
		// �ҋ@����
		m_latency = (float)_wtof(tokens[14].c_str());

		// ������enum�̕ϊ�
		auto data = tokens[15];
		if (data == L"Block") {
			m_type = BlockType::Normal;
		}
		else if (data == L"Bumper") {
			m_type = BlockType::Bumper;
		}
		else if (data == L"Reflector") {
			m_type = BlockType::Reflector;
		}
		else {
			throw BaseException(
				L"�s���Ȓl�ł��B",
				L"if(data == L\"\")",
				L"MoveBlock::MoveBlock()"
			);
		}
	}

	void MoveBlock::OnCreate() {
		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);
		//// �u���b�N�Ƃ̓����蔻��𖳎�
		//ptrColl->AddExcludeCollisionTag(L"Block");
		//ptrColl->SetFixed(true);

		switch (m_type)
		{
		case BlockType::Normal:
			m_block = InstantiateGameObject<Block>(m_transformData);
			break;
		case BlockType::Bumper:
			m_block = InstantiateGameObject<Bumper>(m_transformData);
			break;
		case BlockType::Reflector:
			m_block = InstantiateGameObject<ReflectorBlock>(m_transformData);
			break;
		default:
			throw BaseException(
				L"����`�̒l�ł��B",
				L"switch (m_type)",
				L"void MoveBlock::OnCreate()"
			);
			break;
		}

		auto ptrTrans = GetTransform();
		m_startPosition = ptrTrans->GetPosition();

		m_moveRoot = m_startPosition - m_markPosition; // �����̎擾
		m_moveRoot.normalize(); // ���K��
		m_waitTime = 0;
		m_isWait = true;

		//// �{���̈���ɐݒu
		//m_setPosition = GetTransform()->GetPosition();
		//auto setPos = m_setPosition;
		//setPos.y = -1;
		//GetTransform()->SetPosition(setPos);
		//ApplyTransform();

		AddTag(L"MoveBlock");
	}

	void MoveBlock::MovingBlock() {
		// �f���^�^�C���擾
		const auto& app = App::GetApp();
		const auto delta = app->GetElapsedTime();

		// ���݂̃|�W�V����
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();

		auto rootMoving = m_moveRoot * delta * m_moveSpeed;// �ړ�

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

			if (!m_isWait) ptrTrans->SetPosition(pos);
		}
		else {
			if (m_waitTime > m_latency) {
				m_isWait = false;
			}
			else {
				m_waitTime += delta;
			}
		}
	}

	void MoveBlock::OnUpdate() {
		//auto ptrColl = GetComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::Auto);
		MovingBlock();
		auto currentLocation = GetTransform()->GetPosition();
		m_block->GetTransform()->SetPosition(currentLocation);
	}
}