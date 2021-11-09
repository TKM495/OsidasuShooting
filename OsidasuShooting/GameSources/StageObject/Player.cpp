/*!
@file   Player.cpp
@brief  プレイヤーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate() {
		GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetOwnShadowActive(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<PhysicalBehavior>();
		AddComponent<Gravity>();
		AddComponent<CollisionSphere>();

		ObjectSetUp();
		//ステートマシンの構築
		m_stateMachine.reset(new StateMachine<Player>(GetThis<Player>()));
		//初期ステートの設定
		m_stateMachine->ChangeState(PlayerBulletModeState::Instance());

		AddTag(L"Player");
	}

	void Player::OnUpdate() {
		Move();
		JumpAndHover();
		m_stateMachine->Update();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//Debug::GetInstance()->Log(L"test");
		//auto aabb = other->GetComponent<Collision>()->GetWrappedAABB();
		//auto pos = GetTransform()->GetPosition();

		//if (HitTest::SEGMENT_AABB(pos, pos + Vec3(0.0f, -1.0f, 0.0f), aabb))
		//	Debug::GetInstance()->Log(L"床");
		//else
		//	Debug::GetInstance()->Log(L"壁");
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
	}
	void Player::OnCollisionExit(shared_ptr<GameObject>& other) {
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
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto flg = GroundingDecision::Calculate(GetTransform()->GetPosition());
		if (cntlPad.bLeftTrigger > 128.0f && flg)
			GetComponent<Gravity>()->StartJump(m_jumpVerocity);
	}

	void Player::SpecialSkill() {
		GetStage()->AddGameObject<SpecialCamera>();
	}

	void Player::BulletAim() {
	}
	void Player::BulletLaunch() {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		// 本来はスティックを倒すと発射されるようにする
		if (cntlPad.wPressedButtons & XINPUT_GAMEPAD_A)
			GetStage()->AddGameObject<Bullet>(GetTransform()->GetPosition(), Vec3(0.0f, 0.0f, 1.0f));
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

	// 弾の照準や発射状態（デフォルト）
#pragma region PlayerBulletModeState
	shared_ptr<PlayerBulletModeState> PlayerBulletModeState::Instance() {
		static shared_ptr<PlayerBulletModeState> instance(new PlayerBulletModeState);
		return instance;
	}
	void PlayerBulletModeState::Enter(const shared_ptr<Player>& Obj) {
		Debug::GetInstance()->Log(L"BulletMode");
	}
	void PlayerBulletModeState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		Obj->BulletAim();
		Obj->BulletLaunch();
		if (cntlPad.bRightTrigger > 128.0f) {
			Obj->GetStateMachine()->ChangeState(PlayerBombModeState::Instance());
		}
		if (cntlPad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER &&
			cntlPad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			Obj->GetStateMachine()->ChangeState(PlayerSpecialSkillModeState::Instance());
	}
	void PlayerBulletModeState::Exit(const shared_ptr<Player>& Obj) {}
#pragma endregion

	// 爆弾の照準や発射状態
#pragma region PlayerBombModeState
	shared_ptr<PlayerBombModeState> PlayerBombModeState::Instance() {
		static shared_ptr<PlayerBombModeState> instance(new PlayerBombModeState);
		return instance;
	}
	void PlayerBombModeState::Enter(const shared_ptr<Player>& Obj) {
		Debug::GetInstance()->Log(L"BombMode");
	}
	void PlayerBombModeState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		Obj->BombAim();
		if (cntlPad.bRightTrigger < 128.0f) {
			Obj->GetStateMachine()->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBombModeState::Exit(const shared_ptr<Player>& Obj) {
		Obj->BombLaunch();
	}
#pragma endregion

	// 必殺技発動状態
#pragma region PlayerSpecialSkillModeState
	shared_ptr<PlayerSpecialSkillModeState> PlayerSpecialSkillModeState::Instance() {
		static shared_ptr<PlayerSpecialSkillModeState> instance(new PlayerSpecialSkillModeState);
		return instance;
	}
	void PlayerSpecialSkillModeState::Enter(const shared_ptr<Player>& Obj) {
		Debug::GetInstance()->Log(L"SpecialSkillMode");
		Obj->SpecialSkill();
	}
	void PlayerSpecialSkillModeState::Execute(const shared_ptr<Player>& Obj) {
	}
	void PlayerSpecialSkillModeState::Exit(const shared_ptr<Player>& Obj) {
	}
#pragma endregion
}