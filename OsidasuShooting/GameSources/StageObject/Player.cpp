/*!
@file   Player.cpp
@brief  プレイヤーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate() {
		// シェアオブジェクトに登録（最終的に複数になるので要検討）
		//GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		// 描画コンポーネントの追加
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetOwnShadowActive(true);

		// 影の追加
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_SPHERE");

		// 滑るような挙動用のコンポーネントと重力を追加
		AddComponent<PhysicalBehavior>();
		AddComponent<Gravity>();
		// 当たり判定を追加
		AddComponent<CollisionSphere>();

		ObjectSetUp();
		// 武器ステートマシンの構築
		m_weaponStateMachine.reset(new StateMachine<Player>(GetThis<Player>()));
		// 武器の初期ステートの設定
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());

		// ジャンプ＆ホバー
		m_jumpAndHoverStateMachine.reset(new StateMachine<Player>(GetThis<Player>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());

		// タグの追加
		AddTag(L"Player");
		m_currentArmorPoint = m_defaultArmorPoint;
	}

	void Player::OnUpdate() {
		Move();
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
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

	void Player::Jump() {
		GetComponent<Gravity>()->StartJump(m_jumpVerocity);
	}

	void Player::Hover() {
		if (m_currentHoverTime < 0.0f)
			return;
		GetComponent<Gravity>()->SetGravityVerocityZero();
		m_currentHoverTime -= App::GetApp()->GetElapsedTime();
	}

	void Player::HoverTimeRecovery() {
		if (m_hoverTime > m_currentHoverTime) {
			m_currentHoverTime += App::GetApp()->GetElapsedTime();
		}
		else {
			m_currentHoverTime = m_hoverTime;
		}
	}

	void Player::SpecialSkill() {
		GetStage()->AddGameObject<SpecialCamera>();
	}

	void Player::BulletAimAndLaunch() {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		if (!cntlPad.bConnected)
			return;

		fThumbRY = cntlPad.fThumbRY;
		fThumbRX = cntlPad.fThumbRX;

		Vec3 moveVec(0.0f);
		bool isShot = false;
		if (fThumbRX != 0 || fThumbRY != 0) {
			moveVec = Vec3(fThumbRX, 0.0f, fThumbRY);
			isShot = true;
		}
		else {
			moveVec = Vec3(0.0f);
			isShot = false;
		}
		auto direction = moveVec.normalize() * 3.0f;
		auto userPosition = GetTransform()->GetPosition();
		m_predictionLine.Update(userPosition, userPosition + direction, PredictionLine::Type::Bullet);

		if (isShot)
			GetStage()->AddGameObject<Bullet>(userPosition, direction);
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

		// 移動量
		Vec3 moveVec(0.0f);
		if (fThumbRX != 0 || fThumbRY != 0) {
			moveVec = Vec3(fThumbRX, 0.0f, fThumbRY);
		}
		m_bombPoint += moveVec * delta * 10.0f;
		m_predictionLine.Update(GetTransform()->GetPosition(), m_bombPoint, PredictionLine::Type::Bomb);
	}

	void Player::BombLaunch() {
		GetStage()->AddGameObject<Bomb>(m_predictionLine, GetTransform()->GetPosition(), m_bombPoint);
	}

	void Player::KnockBack(const Vec3& knockBackDirection, float knockBackAmount) {
		float knockBackCorrection;
		if (m_currentArmorPoint > 0)
		{
			knockBackCorrection = 1;
			m_currentArmorPoint -= 5;
		}
		else
		{
			knockBackCorrection = 5.0f;
		}
		GetComponent<PhysicalBehavior>()->
			Impact(knockBackDirection, knockBackAmount * knockBackCorrection);
		Debug::GetInstance()->Log(m_currentArmorPoint);
	}

	void Player::Respawn() {
	}

	// 武器用ステート
	// 弾の照準や発射状態（デフォルト）
#pragma region PlayerBulletModeState
	shared_ptr<PlayerBulletModeState> PlayerBulletModeState::Instance() {
		static shared_ptr<PlayerBulletModeState> instance(new PlayerBulletModeState);
		return instance;
	}
	void PlayerBulletModeState::Enter(const shared_ptr<Player>& Obj) {}
	void PlayerBulletModeState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		Obj->BulletAimAndLaunch();
		if (cntlPad.bRightTrigger > 128.0f) {
			Obj->GetWeaponStateMachine()->ChangeState(PlayerBombModeState::Instance());
		}
		if (cntlPad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER &&
			cntlPad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			Obj->GetWeaponStateMachine()->ChangeState(PlayerSpecialSkillModeState::Instance());
	}
	void PlayerBulletModeState::Exit(const shared_ptr<Player>& Obj) {}
#pragma endregion

	// 爆弾の照準や発射状態
#pragma region PlayerBombModeState
	shared_ptr<PlayerBombModeState> PlayerBombModeState::Instance() {
		static shared_ptr<PlayerBombModeState> instance(new PlayerBombModeState);
		return instance;
	}
	void PlayerBombModeState::Enter(const shared_ptr<Player>& Obj) {}
	void PlayerBombModeState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		Obj->BombAim();
		if (cntlPad.bRightTrigger < 128.0f) {
			Obj->GetWeaponStateMachine()->ChangeState(PlayerBulletModeState::Instance());
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
		Obj->SpecialSkill();
	}
	void PlayerSpecialSkillModeState::Execute(const shared_ptr<Player>& Obj) {
	}
	void PlayerSpecialSkillModeState::Exit(const shared_ptr<Player>& Obj) {
	}
#pragma endregion

	// ジャンプ
#pragma region PlayerJumpState
	shared_ptr<PlayerJumpState> PlayerJumpState::Instance() {
		static shared_ptr<PlayerJumpState> instance(new PlayerJumpState);
		return instance;
	}
	void PlayerJumpState::Enter(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.bLeftTrigger > 128.0f) {
			m_isPushedLeftTrigger = true;
		}
	}
	void PlayerJumpState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.bLeftTrigger > 128.0f) {
			if (!m_isPushedLeftTrigger) {
				Obj->Jump();
				Obj->GetJumpAndHoverStateMachine()->ChangeState(PlayerHoverState::Instance());
			}
		}
		else {
			m_isPushedLeftTrigger = false;
		}
		Obj->HoverTimeRecovery();
	}
	void PlayerJumpState::Exit(const shared_ptr<Player>& Obj) {}
#pragma endregion
	// ホバー
#pragma region PlayerHoverState
	shared_ptr<PlayerHoverState> PlayerHoverState::Instance() {
		static shared_ptr<PlayerHoverState> instance(new PlayerHoverState);
		return instance;
	}
	void PlayerHoverState::Enter(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.bLeftTrigger > 128.0f) {
			m_isPushedLeftTrigger = true;
		}
		m_groundingDecision.SetRadius(Obj->GetTransform()->GetScale());
	}
	void PlayerHoverState::Execute(const shared_ptr<Player>& Obj) {
		const auto& cntlPad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlPad.bLeftTrigger > 128.0f) {
			if (!m_isPushedLeftTrigger)
				Obj->Hover();
		}
		else {
			m_isPushedLeftTrigger = false;
		}

		bool flg = m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition());
		if (flg)
			Obj->GetJumpAndHoverStateMachine()->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerHoverState::Exit(const shared_ptr<Player>& Obj) {}
#pragma endregion
}