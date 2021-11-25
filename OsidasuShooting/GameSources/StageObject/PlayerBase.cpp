/*!
@file   PlayerBase.cpp
@brief  プレイヤーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerBase::OnCreate() {
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
		m_currentHoverTime = m_hoverTime;
		m_bombCount = m_defaultBombCount;
		m_initialPosition = GetTransform()->GetPosition();

		// 接地判定の情報を初期化
		m_groundingDecision.SetRadius(GetTransform()->GetScale());
	}

	void PlayerBase::OnUpdate() {
		// 復帰中で接地しているかつ
		if (m_isDuringReturn &&
			m_groundingDecision.Calculate(GetTransform()->GetPosition())) {
			// 一定時間経過したら復帰が終了した判定に
			if (m_returnTimer.Count()) {
				m_isDuringReturn = false;
			}
		}

		// テスト用の処理（ダメージを受けたら赤くなる）
		if (m_isDuringReturn) {
			GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else {
			GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// 入力の更新
		InputUpdate();
		// 移動処理
		Move();
		// テストコード
		TestFanc();
		// 爆弾のリロード
		BombReload();
		// 各種ステートマシンの更新
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
		// アーマー回復フラグがtrueの場合
		if (m_isRestoreArmor)
			// アーマーを回復
			ArmorRecovery();
	}

	void PlayerBase::Move() {
		auto physicalComp = GetComponent<PhysicalBehavior>();
		physicalComp->Move(m_inputData.MoveDirection, m_moveSpeed);
	}

	void PlayerBase::Jump() {
		GetComponent<Gravity>()->StartJump(m_jumpVerocity);
	}

	void PlayerBase::Hover() {
		// ホバー可能時間が0以上の場合はホバー
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
		//GetStage()->AddGameObject<SpecialCamera>();
	}

	void PlayerBase::BulletAimAndLaunch() {
		auto userPosition = GetTransform()->GetPosition();
		auto bulletAim = BulletAimCorrection(m_inputData.BulletAim.normalize());

		Ray ray(userPosition, bulletAim);
		// 予測線はStartとEndの2点の情報が必要
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);

		// 弾の発射
		if (bulletAim != Vec3(0.0f) && m_bulletTimer.Count()) {
			m_bulletTimer.Reset();
			GetStage()->AddGameObject<Bullet>(GetThis<PlayerBase>(), ray);
		}
	}

	Vec3 PlayerBase::BulletAimCorrection(const Vec3& launchDirection) {
		vector<Vec3> positions;

		// プレイヤーの取得
		const auto& players = PlayerManager::GetInstance()->GetAllPlayer();
		for (auto player : players) {
			if (player == GetThis<PlayerBase>())
				continue;
			auto pos = player->GetTransform()->GetPosition();
			if (InViewRange(launchDirection, pos))
				positions.push_back(pos);
		}

		// リストが空の場合補正しない
		if (positions.size() <= 0)
			return launchDirection;

		// 最も自身に近い位置を求める
		auto closestPosition = Vec3(INFINITY);
		for (auto position : positions)
		{
			auto direction = position - GetTransform()->GetPosition();
			if (direction.lengthSqr() < closestPosition.lengthSqr())
				closestPosition = position;
		}

		auto direction = closestPosition - GetTransform()->GetPosition();
		// y座標を合わせる
		direction.y = launchDirection.y;
		return direction.normalize();
	}

	bool PlayerBase::InViewRange(const Vec3& aimDirection, const Vec3& position)
	{
		// 自分からpositionへのベクトル
		Vec3 direction = position - GetTransform()->GetPosition();
		// 照準方向から見たtargetPosとの角度
		float deg = Utility::GetTwoVectorAngle(aimDirection, direction.normalize());
		// 角度が視野の範囲内かどうか(angleは左右合わせての角度なので÷2)
		return deg < (m_correctAngle / 2.0f);
	}

	void PlayerBase::BombAim() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_bombPoint += m_inputData.BombAim * delta * 20.0f;
		m_predictionLine.Update(GetTransform()->GetPosition(), m_bombPoint, PredictionLine::Type::Bomb);
	}

	void PlayerBase::BombReload() {
		// 現在の爆弾の数が最大数以上の場合は何もしない
		if (m_bombCount < m_defaultBombCount) {
			// 一定の時間が経過したら
			if (m_bombReload.Count()) {
				// 残弾を増やし、タイマーをリセット
				m_bombCount++;
				m_bombReload.Reset();
			}
		}
	}

	void PlayerBase::BombLaunch() {
		GetStage()->AddGameObject<Bomb>(GetThis<PlayerBase>(),
			m_predictionLine, GetTransform()->GetPosition(), m_bombPoint);
	}

	void PlayerBase::ArmorRecovery() {
		// アーマーが0になってから一定時間後に回復
		if (!m_armorRecoveryTimer.Count())
			return;

		// m_defaultArmorPointを超えたら回復停止
		if (m_currentArmorPoint >= m_defaultArmorPoint) {
			m_currentArmorPoint = m_defaultArmorPoint;
			m_isRestoreArmor = false;
			m_armorRecoveryTimer.Reset();
		}
		m_currentArmorPoint += 10.0f * App::GetApp()->GetElapsedTime();
	}

	void PlayerBase::KnockBack(const KnockBackData& data) {
		m_aggriever = data.Aggriever;
		m_isDuringReturn = true;
		m_returnTimer.Reset();
		// ノックバック倍率
		float knockBackCorrection;
		// アーマーが回復中でない　かつ　アーマーが0より大きい
		if (m_currentArmorPoint > 0 && !m_isRestoreArmor) {
			knockBackCorrection = 1.0f;
		}
		else {
			knockBackCorrection = 5.0f;
			m_isRestoreArmor = true;
		}
		// ダメージ判定
		switch (data.Type) {
		case KnockBackData::Category::Bullet:
			m_currentArmorPoint -= 10;
			break;
		case KnockBackData::Category::Bomb:
			m_currentArmorPoint -= 5;
			break;
		default:
			break;
		}
		GetComponent<PhysicalBehavior>()->Impact(
			data.Direction, data.Amount * knockBackCorrection);
	}

	void PlayerBase::Respawn() {
		// 復帰中に死んだ場合加害者に倒した通知を行う
		if (m_isDuringReturn) {
			m_aggriever->KilledPlayer();
		}
		m_isDuringReturn = false;
		GetTransform()->SetPosition(m_initialPosition);
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// アーマーを0にする
		if (keyState.m_bPressedKeyTbl['0']) {
			m_currentArmorPoint = 0.0f;
			m_isRestoreArmor = true;
			Debug::GetInstance()->Log(L"Test:Armor0");
		}
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
		if (Obj->m_inputData.IsInvokeSpecialSkill) {
			// 現在は遷移しないようにする
			//Obj->m_weaponStateMachine->ChangeState(PlayerSpecialSkillModeState::Instance());
		}
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
		// 爆弾の残弾がある場合
		if (Obj->m_bombCount > 0) {
			// 弾モードへ遷移時に爆弾を発射
			Obj->BombLaunch();
			// 残弾を減らす
			Obj->m_bombCount--;
		}
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
			Obj->m_isInput = true;
		}
	}
	void PlayerBase::PlayerJumpState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// 入力がある場合
		if (Obj->m_inputData.IsJumpOrHover) {
			// 遷移時に入力があった場合はジャンプしない
			if (!Obj->m_isInput) {
				Obj->Jump();
				Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerHoverState::Instance());
			}
		}
		else {
			Obj->m_isInput = false;
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
			Obj->m_isInput = true;
		}
	}
	void PlayerBase::PlayerHoverState::Execute(const shared_ptr<PlayerBase>& Obj) {
		if (Obj->m_inputData.IsJumpOrHover) {
			// 遷移時に入力があった場合ホバーを行わない（一度離す必要がある）
			if (!Obj->m_isInput)
				Obj->Hover();
		}
		else {
			Obj->m_isInput = false;
		}

		// 接地した場合
		if (Obj->m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// ジャンプステートへ遷移
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion
}