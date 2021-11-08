/*!
@file SpecialCamera.cpp
@brief �K�E�Z���g�����Ƃ��̃J��������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpecialCamera::SpecialCamera(const shared_ptr<Stage>& stage)
		:
		GameObject(stage),
		m_startPos(0),
		m_startRot(0),

		m_lPos(0),

		m_move(0),
		m_totalTime(0),
		m_easingTime(1.7f),

		m_playerPos(0, 0, 0),
		m_playerRot(0, 0, 0)
	{}


	// �v���C���[�̈ʒu���擾����
	void SpecialCamera::PlayerTrans()
	{
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerTrans = ptrPlayer->GetComponent<Transform>();
		m_playerPos = playerTrans->GetPosition();
		m_playerRot = playerTrans->GetRotation();
	}

	// �^�[�Q�b�g(�v���C���[)�̕�������
	void  SpecialCamera::LookAtTarget()
	{
		auto trans = GetComponent<Transform>();

		// �ΏۂƎ��g�̈ʒu���擾
		Vec3 targetPos = m_playerPos;
		Vec3 cameraPos = trans->GetPosition();
		// �����̊p�x�v�Z
		Vec2 trgPos2d = Vec2(targetPos.x, targetPos.y);
		Vec2 cmrPos2d = Vec2(cameraPos.x, cameraPos.y);

		Vec2 direction = trgPos2d - cmrPos2d;
		auto angle = -atan2(direction.y, direction.x);

		trans->SetRotation(cameraPos.x, angle, angle);



	}

	// �I�u�W�F�N�g�̐���
	void SpecialCamera::OnCreate()
	{
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		auto trans = GetComponent<Transform>();
		PlayerTrans();

		trans->SetRotation(m_playerRot);

		m_cameraPos[0] = m_playerPos + Vec3(-2, 1, 1);
		m_cameraPos[1] = m_playerPos + Vec3(-1.5f, -1, -2);

		trans->SetPosition(m_cameraPos[0]);
	}

	// �I�u�W�F�N�g�̍X�V
	void SpecialCamera::OnUpdate()
	{
		float deltaTime = App::GetApp()->GetElapsedTime();
		m_totalTime += deltaTime;

		// �g�����X���擾
		PlayerTrans();
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();

		LookAtTarget();

		m_move = 1 - m_move;
		Vec3 TargetPos, TargetRot;

		Easing<Vec3> cameraMove; TargetPos = cameraMove.EaseInOut(
			EasingType::Exponential, m_cameraPos[0], m_cameraPos[1], m_totalTime, m_easingTime);
		trans->SetPosition(TargetPos);
	}

}
