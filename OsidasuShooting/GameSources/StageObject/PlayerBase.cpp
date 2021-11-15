/*!
@file   PlayerBase.cpp
@brief  プレイヤーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerBase::OnCreate() {
		// シェアオブジェクトに登録（最終的に複数になるので要検討）
		//GetStage()->SetSharedGameObject(L"PlayerBase", GetThis<PlayerBase>());

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
		m_weaponStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		// 武器の初期ステートの設定
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());

		// ジャンプ＆ホバー
		m_jumpAndHoverStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());

		// タグの追加
		AddTag(L"Player");
		m_currentArmorPoint = m_defaultArmorPoint;
	}

	void PlayerBase::OnUpdate() {
		InputUpdate();
		Move();
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
	}

	void PlayerBase::Move() {
		auto physicalComp = GetComponent<PhysicalBehavior>();
		physicalComp->Move(m_inputData.MoveDirection, m_moveSpeed);
	}

	void PlayerBase::Jump() {
		GetComponent<Gravity>()->StartJump(m_jumpVerocity);
	}

	void PlayerBase::Hover() {
		if (m_currentHoverTime < 0.0f)
			return;
		GetComponent<Gravity>()->SetGravityVerocityZero();
		m_currentHoverTime -= App::GetApp()->GetElapsedTime();
	}

	void PlayerBase::HoverTimeRecovery() {
		if (m_hoverTime > m_currentHoverTime) {
			m_currentHoverTime += App::GetApp()->GetElapsedTime();
		}
		else {
			m_currentHoverTime = m_hoverTime;
		}
	}

	void PlayerBase::SpecialSkill() {
		GetStage()->AddGameObject<SpecialCamera>();
	}

	void PlayerBase::BulletAimAndLaunch() {
		auto userPosition = GetTransform()->GetPosition();
		Ray ray(userPosition, m_inputData.BulletAim.normalize());
		// 予測線はStartとEndの2点の情報が必要
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);

		if (m_inputData.BulletAim != Vec3(0.0f) && m_bulletTimer.Count()) {
			m_bulletTimer.Reset();
			GetStage()->AddGameObject<Bullet>(GetThis<PlayerBase>(), ray);
		}
	}
	void PlayerBase::BombAim() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_bombPoint += m_inputData.BombAim * delta * 20.0f;
		m_predictionLine.Update(GetTransform()->GetPosition(), m_bombPoint, PredictionLine::Type::Bomb);
	}

	void PlayerBase::BombLaunch() {
		GetStage()->AddGameObject<Bomb>(m_predictionLine, GetTransform()->GetPosition(), m_bombPoint);
	}

	void PlayerBase::KnockBack(const Vec3& knockBackDirection, float knockBackAmount) {
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

	void PlayerBase::Respawn() {
	}

	// 武器用ステート
	// 弾の照準や発射状態（デフォルト）
#pragma region PlayerBulletModeState
	shared_ptr<PlayerBase::PlayerBulletModeState> PlayerBase::PlayerBulletModeState::Instance() {
		static shared_ptr<PlayerBulletModeState> instance(new PlayerBulletModeState);
		return instance;
	}
	void PlayerBase::PlayerBulletModeState::Enter(const shared_ptr<PlayerBase>& Obj) {}
	void PlayerBase::PlayerBulletModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// 弾の照準と発射
		Obj->BulletAimAndLaunch();
		// 爆弾モードへの遷移
		if (Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBombModeState::Instance());
		}
		// 必殺技モードへの遷移
		if (Obj->m_inputData.IsInvokeSpecialSkill)
			Obj->m_weaponStateMachine->ChangeState(PlayerSpecialSkillModeState::Instance());
	}
	void PlayerBase::PlayerBulletModeState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion

	// 爆弾の照準や発射状態
#pragma region PlayerBombModeState
	shared_ptr<PlayerBase::PlayerBombModeState> PlayerBase::PlayerBombModeState::Instance() {
		static shared_ptr<PlayerBombModeState> instance(new PlayerBombModeState);
		return instance;
	}
	void PlayerBase::PlayerBombModeState::Enter(const shared_ptr<PlayerBase>& Obj) {}
	void PlayerBase::PlayerBombModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// 爆弾の照準
		Obj->BombAim();
		// 爆弾モードを終了（弾モードへ遷移）
		if (!Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBase::PlayerBombModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
		// 弾モードへ遷移時に爆弾を発射
		Obj->BombLaunch();
	}
#pragma endregion

	// 必殺技発動状態
#pragma region PlayerSpecialSkillModeState
	shared_ptr<PlayerBase::PlayerSpecialSkillModeState> PlayerBase::PlayerSpecialSkillModeState::Instance() {
		static shared_ptr<PlayerSpecialSkillModeState> instance(new PlayerSpecialSkillModeState);
		return instance;
	}
	void PlayerBase::PlayerSpecialSkillModeState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// 現時点では一回だけ
		Obj->SpecialSkill();
	}
	void PlayerBase::PlayerSpecialSkillModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
	}
	void PlayerBase::PlayerSpecialSkillModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
	}
#pragma endregion

	// ジャンプ
#pragma region PlayerJumpState
	shared_ptr<PlayerBase::PlayerJumpState> PlayerBase::PlayerJumpState::Instance() {
		static shared_ptr<PlayerJumpState> instance(new PlayerJumpState);
		return instance;
	}
	void PlayerBase::PlayerJumpState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// 遷移時に入力がある場合
		if (Obj->m_inputData.IsJumpOrHover) {
			// フラグを立てる
			m_isPushed = true;
		}
	}
	void PlayerBase::PlayerJumpState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// 入力がある場合
		if (Obj->m_inputData.IsJumpOrHover) {
			// 遷移時に入力があった場合はジャンプしない
			if (!m_isPushed) {
				Obj->Jump();
				Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerHoverState::Instance());
			}
		}
		else {
			m_isPushed = false;
		}
		// ホバー可能時間回復
		Obj->HoverTimeRecovery();
	}
	void PlayerBase::PlayerJumpState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion
	// ホバー
#pragma region PlayerHoverState
	shared_ptr<PlayerBase::PlayerHoverState> PlayerBase::PlayerHoverState::Instance() {
		static shared_ptr<PlayerHoverState> instance(new PlayerHoverState);
		return instance;
	}
	void PlayerBase::PlayerHoverState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// 遷移時に入力がある場合
		if (Obj->m_inputData.IsJumpOrHover) {
			// フラグを立てる
			m_isPushed = true;
		}
		// 接地判定の情報を初期化
		m_groundingDecision.SetRadius(Obj->GetTransform()->GetScale());
	}
	void PlayerBase::PlayerHoverState::Execute(const shared_ptr<PlayerBase>& Obj) {
		if (Obj->m_inputData.IsJumpOrHover) {
			// 遷移時に入力があった場合ホバーを行わない（一度離す必要がある）
			if (!m_isPushed)
				Obj->Hover();
		}
		else {
			m_isPushed = false;
		}

		// 接地した場合
		if (m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// ジャンプステートへ遷移
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion
}