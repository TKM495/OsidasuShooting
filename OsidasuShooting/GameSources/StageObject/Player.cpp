/*!
@file   Player.cpp
@brief  �v���C���[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<PhysicalBehavior>();
		AddComponent<Gravity>();
		AddComponent<CollisionSphere>();

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Bullet");
		efkComp->SetScale(Vec3(1.0f));
		ObjectSetUp();
		//�X�e�[�g�}�V���̍\�z
		m_stateMachine.reset(new StateMachine<Player>(GetThis<Player>()));
		//�����X�e�[�g�̐ݒ�
		m_stateMachine->ChangeState(PlayerBulletModeState::Instance());
	}

	void Player::OnUpdate() {
		Move();
		JumpAndHover();
		m_stateMachine->Update();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
	}

	void Player::Move() {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto physicalComp = GetComponent<PhysicalBehavior>();

		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		if (!cntlPad.bConnected)
			return;

		fThumbLY = cntlPad.fThumbLY;
		fThumbLX = cntlPad.fThumbLX;

		Vec3 moveVec(0.0f);
		if (fThumbLX != 0 || fThumbLY != 0)
		{
			moveVec = Vec3(fThumbLX, 0.0f, fThumbLY);
		}
		physicalComp->Move(moveVec, m_moveSpeed);
	}

	void Player::JumpAndHover() {
	}

	void Player::SpecialSkill() {
	}

	void Player::BulletAim() {
	}
	void Player::BulletLaunch() {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto efkComp = GetComponent<EfkComponent>();
		// �{���̓X�e�B�b�N��|���Ɣ��˂����悤�ɂ���
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A)
			efkComp->Play();
		efkComp->AddLocation(Vec3(0.0f, 0.0f, 1.0f));
	}
	void Player::BombAim() {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto delta = App::GetApp()->GetElapsedTime();
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		if (!cntlPad.bConnected)
			return;

		fThumbRY = cntlPad.fThumbRY;
		fThumbRX = cntlPad.fThumbRX;

		Vec3 moveVec(0.0f);
		if (fThumbRX != 0 || fThumbRY != 0)
		{
			moveVec = Vec3(fThumbRX, 0.0f, fThumbRY);
		}
		m_bombPoint += moveVec * delta * 10.0f;
		line.SetActive(true);
		line.Update(GetTransform()->GetPosition(), m_bombPoint);
	}

	void Player::BombLaunch() {
		line.SetActive(false);
	}

#pragma region PlayerBulletModeState
	shared_ptr<PlayerBulletModeState> PlayerBulletModeState::Instance() {
		static shared_ptr<PlayerBulletModeState> instance(new PlayerBulletModeState);
		return instance;
	}
	void PlayerBulletModeState::Enter(const shared_ptr<Player>& Obj) {
	}
	void PlayerBulletModeState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];

		Obj->BulletAim();
		Obj->BulletLaunch();
		Debug::GetInstance()->Log(L"Bullet");
		if (cntlPad.bRightTrigger > 128.0f) {
			Obj->GetStateMachine()->ChangeState(PlayerBombModeState::Instance());
		}
	}
	void PlayerBulletModeState::Exit(const shared_ptr<Player>& Obj) {}
#pragma endregion

#pragma region PlayerBombModeState
	shared_ptr<PlayerBombModeState> PlayerBombModeState::Instance() {
		static shared_ptr<PlayerBombModeState> instance(new PlayerBombModeState);
		return instance;
	}
	void PlayerBombModeState::Enter(const shared_ptr<Player>& Obj) {
	}
	void PlayerBombModeState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		Debug::GetInstance()->Log(L"Bomb");
		Obj->BombAim();
		if (cntlPad.bRightTrigger < 128.0f) {
			Obj->GetStateMachine()->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBombModeState::Exit(const shared_ptr<Player>& Obj) {
		Obj->BombLaunch();
	}
#pragma endregion
}