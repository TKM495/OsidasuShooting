/*!
@file   PlayerBase.cpp
@brief  プレイヤーの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	PlayerBase::PlayerBase(const shared_ptr<Stage>& stage,
		const TransformData& transData,
		PlayerNumber playerNumber,
		PlayerType playerType)
		: AdvancedGameObject(stage), m_playerType(playerType),
		m_initialPosition(0.0f),
		m_moveSpeed(20.0f), m_predictionLine(stage, 10, 2.0f),
		m_bombPoint(Vec3(0.0f)), m_jumpVerocity(Vec3(0.0f, 11.0f, 0.0f)),
		m_defaultEnergy(100.0f), m_currentEnergy(0.0f),
		m_bulletTimer(0.1f, true), m_bombCoolTimeTimer(1, true),
		m_isInput(false), m_playerNumber(playerNumber),
		m_defaultBombCount(5), m_correctAngle(40.0f),
		m_isDuringReturn(false), m_groundingDecision(), m_countKilledPlayer(0),
		m_returnTimer(0.5f), m_lastFrontDirection(Vec3(0.0f)), m_smokeTimer(0.2f),
		m_deadCount(0), m_invincibleTimer(3.0f, true), m_isInvincible(false),
		m_armorZeroWhenKnockBackMagnification(5), m_energyRecoveryAmount(10),
		m_bombAimMovingDistance(20), m_respawnTimer(3.0f), m_isActive(true)
	{
		m_transformData = transData;
		m_transformData.Scale *= 2.0f;
		auto rot = m_transformData.Rotation;
		m_lastFrontDirection = Vec3(sinf(rot.y), 0.0f, cosf(rot.y));
		// 以下のタグを持つオブジェクトを判定から除外
		m_groundingDecision.AddNotDecisionTag(L"Bomb");
		m_groundingDecision.AddNotDecisionTag(L"Bullet");
	}

	void PlayerBase::OnCreate() {
		// XMLのデータを取得
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		// プレイヤーの色情報を取得
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/PlayerColor");
		// 4プレイヤー分の色を空白で4つのデータに分ける
		auto colorStr = DataExtracter::DelimitData(data, L' ');
		// 自身のプレイヤー番号に応じた色データをRGBAに分類
		auto color = DataExtracter::DelimitData(colorStr[(UINT)m_playerNumber]);
		// 分類したものをCol4に変換
		m_color = DataExtracter::ColorDataExtraction(color);
		// 0～1に変換
		m_color = Utility::ConvertColorZeroToOne(m_color);

		// プレイヤーのモデルを追加
		m_model = InstantiateGameObject<PlayerModel>(GetThis<PlayerBase>(), m_transformData);

		// 予測線の色を設定
		m_predictionLine.SetColor(m_color);

		// 滑るような挙動用のコンポーネントと重力を追加
		AddComponent<PhysicalBehavior>();
		auto gravity = AddComponent<Gravity>();
		//auto defaultGravity = gravity->GetGravity();
		//// 重力をデフォルトの3倍に設定
		//gravity->SetGravity(defaultGravity * 3);
				// 外部ファイルからステータスを読み込み
		StatusLoad();

		// 当たり判定を追加
		AddComponent<CollisionSphere>()->SetDrawActive(false);

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Jump", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Hover", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Smoke", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale), true);
		efkComp->SetEffectResource(L"BombPlus", TransformData(Vec3(0), m_transformData.Scale));
		efkComp->SetEffectResource(L"Respawn", TransformData(Vec3(0.0f, -0.5f, 0.0f)));
		// 落ちたときのエフェクトの代わり
		efkComp->SetEffectResource(L"Explosion", TransformData(Vec3(0.0f), Vec3(1.0f, 5.0f, 1.0f)));

		// 武器ステートマシンの構築と設定
		m_weaponStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		// ジャンプ＆ホバーステートマシンの構築と設定
		m_jumpAndHoverStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
		// リスポーン用ステートマシンの構築と設定
		m_respawnStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_respawnStateMachine->ChangeState(PlayerNormalState::Instance());

		// タグの追加
		AddTag(L"Player");

		// 各値の初期化
		ParameterReset();
		m_initialPosition = GetTransform()->GetPosition();
		SoundManager::GetInstance()->InitPlayOverlap(L"HoverSE", 0.06f);
		// 接地判定の情報を初期化
		m_groundingDecision.SetRadius(GetTransform()->GetScale());
		//Debug::GetInstance()->Log(m_lastFrontDirection);
		//m_predictionLine.Update(GetTransform()->GetPosition(),
		//	GetTransform()->GetPosition() + m_lastFrontDirection * 5, PredictionLine::Type::Bullet);
		Debug::GetInstance()->Log(m_initialPosition);
	}

	void PlayerBase::OnUpdate() {
		m_respawnStateMachine->Update();
	}

	void PlayerBase::NormalUpdate() {
		// 復帰中で接地しているかつ
		if (m_isDuringReturn &&
			m_groundingDecision.Calculate(GetTransform()->GetPosition())) {
			// 一定時間経過したら復帰が終了した判定に
			if (m_returnTimer.Count()) {
				m_isDuringReturn = false;
			}
		}

		// auto gameStage = GetTypeStage<GameStage>(false);
		//// 現在のステージがGameStage
		// if (gameStage) {
		//	switch (gameStage->GetCurrentGameState())
		//	{
		//	case GameStage::GameState::PLAYING:
		//		// 入力の更新
		//		InputUpdate();
		//		break;
		//	}
		// }

		InputUpdate();

		// 移動処理
		Move();
		// テストコード
		TestFanc();

		// 無敵処理
		Invincible();
		// 各種ステートマシンの更新
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
		// 接地しているときだけエネルギーを回復
		if (m_groundingDecision.Calculate(GetTransform()->GetPosition()))
			EnergyRecovery();
		// 爆弾のクールタイムの更新
		m_bombCoolTimeTimer.Count();
		// 吹っ飛びエフェクトの描画
		KnockBackEffectDrawing();
	}

	void PlayerBase::Move() {
		auto physicalComp = GetComponent<PhysicalBehavior>();
		physicalComp->Move(m_inputData.MoveDirection, m_moveSpeed);
		auto efkComp = GetComponent<EfkComponent>();

		// 移動していて接地している場合
		if (m_inputData.MoveDirection != Vec3(0.0f) &&
			m_groundingDecision.Calculate(GetTransform()->GetPosition())) {
			if (m_smokeTimer.Count()) {
				efkComp->Play(L"Smoke");
				m_smokeTimer.Reset();
			}
		}
	}

	void PlayerBase::Invincible() {
		if (m_invincibleTimer.Count()) {
			m_isInvincible = false;
		}
		else {
			auto time = m_invincibleTimer.GetElaspedTime() * 10;
			auto flg = ((int)time % 2) == 0;
			m_model.lock()->SetDrawActive(flg);
		}
	}

	void PlayerBase::Jump() {
		GetComponent<Gravity>()->StartJump(m_jumpVerocity);
		// エフェクトと効果音の再生
		GetComponent<EfkComponent>()->Play(L"Jump");
		SoundManager::GetInstance()->Play(L"JumpSE", 0, 0.3f);
	}

	void PlayerBase::Hover() {
		m_isHoverMode = true;
		auto delta = App::GetApp()->GetElapsedTime();
		// エネルギーがない場合はホバーを停止
		if (!DecrementEnergy(m_energyRequiredInHover * delta)) {
			StopHover();
			return;
		}
		GetComponent<Gravity>()->SetGravityVerocityZero();

		// ホバーエフェクト
		auto efkComp = GetComponent<EfkComponent>();
		if (!efkComp->IsPlaying(L"Hover")) {
			efkComp->Play(L"Hover");
		}
		else {
			efkComp->SyncPosition(L"Hover");
		}
		SoundManager::GetInstance()->PlayOverlap(L"HoverSE", 0.4f);
	}

	Vec3 PlayerBase::BulletAim() {
		// 位置と方向
		Ray ray(
			GetTransform()->GetPosition(),
			BulletAimCorrection(m_inputData.BulletAim.normalize())
		);
		// 予測線はStartとEndの2点の情報が必要
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);
		// 照準方向を正面にして、正面方向を返す
		return TurnFrontToDirection(ray.Direction);
	}

	void PlayerBase::BulletLaunch(const Vec3& bulletAim) {
		if (bulletAim == Vec3(0))
			return;

		// 弾の発射
		if (m_bulletTimer.Count() && m_inputData.IsFire) {
			// エネルギーを使える場合弾を発射
			if (DecrementEnergy(m_energyRequiredInBulletLaunch)) {
				m_bulletTimer.Reset();
				InstantiateGameObject<Bullet>(GetThis<PlayerBase>(), bulletAim, m_bulletPower);
				SoundManager::GetInstance()->Play(L"ShotSE", 0, 0.3f);
			}
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
		for (auto position : positions) {
			auto direction = position - GetTransform()->GetPosition();
			if (direction.lengthSqr() < closestPosition.lengthSqr())
				closestPosition = position;
		}

		auto direction = closestPosition - GetTransform()->GetPosition();
		// y座標を合わせる
		direction.y = launchDirection.y;
		return direction.normalize();
	}

	bool PlayerBase::InViewRange(const Vec3& aimDirection, const Vec3& position) {
		// 自分からpositionへのベクトル
		Vec3 direction = position - GetTransform()->GetPosition();
		// 照準方向から見たtargetPosとの角度
		float deg = Utility::GetTwoVectorAngle(aimDirection, direction.normalize());
		// 角度が視野の範囲内かどうか(angleは左右合わせての角度なので÷2)
		return deg < (m_correctAngle / 2.0f);
	}

	void PlayerBase::BombAim() {
		auto delta = App::GetApp()->GetElapsedTime();
		m_bombPoint += m_inputData.BombAim * delta * m_bombAimMovingDistance;
		m_predictionLine.Update(GetTransform()->GetPosition(), m_bombPoint, PredictionLine::Type::Bomb);
		TurnFrontToDirection(m_bombPoint - GetTransform()->GetPosition());
	}

	void PlayerBase::BombLaunch() {
		InstantiateGameObject<Bomb>(GetThis<PlayerBase>(),
			m_predictionLine, GetTransform()->GetPosition(), m_bombPoint, m_bombPower);
		SoundManager::GetInstance()->Play(L"ThrowBombSE", 0, 0.3f);
	}

	Vec3 PlayerBase::TurnFrontToDirection(const Vec3& direction) {
		Vec3 rot(0.0f);
		// directionがVec3(0.0f)だったら前回の方向のまま維持
		Vec3 _direction = direction != Vec3(0.0f) ? direction : m_lastFrontDirection;
		_direction.y = 0;
		// 方向に正面を向ける
		auto rad = atan2f(-_direction.z, _direction.x) - XM_PIDIV2;
		rot.y = rad;
		GetTransform()->SetRotation(rot);
		m_lastFrontDirection = _direction;
		return _direction;
	}

	void PlayerBase::EnergyRecovery() {
		// デフォルト値を超えたら回復停止
		if (m_currentEnergy >= m_defaultEnergy) {
			m_currentEnergy = m_defaultEnergy;
			return;
		}
		m_currentEnergy +=
			m_energyRecoveryAmount * App::GetApp()->GetElapsedTime();
	}

	void PlayerBase::StopHover() {
		m_isHoverMode = false;
		GetComponent<EfkComponent>()->Stop(L"Hover");
		OnStopHover();
	}

	void PlayerBase::StatusLoad() {
		// XMLのデータを取得
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		wstring type;
		switch (m_playerType) {
		case PlayerType::Laser:
			type = L"LaserStatus";
			break;
		case PlayerType::Missile:
			type = L"MissileStatus";
			break;
		default:
			throw BaseException(
				L"定義されていないか未実装です。",
				L"switch (m_playerType)",
				L"PlayerBase::StatusLoad()");
			break;
		}
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/" + type);
		// 4プレイヤー分の色を空白で4つのデータに分ける
		auto statusStr = DataExtracter::DelimitData(data, L' ');
		// 文字列のデータを数値に変換
		vector<float> status;
		for (auto stat : statusStr) {
			status.push_back((float)_wtof(stat.c_str()));
		}

		// 移動速度
		m_moveSpeed = status[0];
		// ジャンプ量
		m_jumpVerocity = Vec3(0, status[1], 0);
		// 弾の発射に必要なエネルギー
		m_energyRequiredInBulletLaunch = status[2];
		// ホバーに必要なエネルギー
		m_energyRequiredInHover = status[3];
		// エネルギーの回復速度
		m_energyRecoveryAmount = status[4];
		// 弾の威力
		m_bulletPower = status[5];
		// 爆弾の威力
		m_bombPower = status[6];
		// 弾の連射速度
		m_bulletTimer.SetIntervalTime(status[7], true);
		m_bombCoolTimeTimer.SetIntervalTime(status[8], true);
		auto defaultGravity = GetComponent<Gravity>()->GetGravity();
		// 重力をデフォルトの3倍に設定
		GetComponent<Gravity>()->SetGravity(defaultGravity * status[9]);
	}

	void PlayerBase::ParameterReset() {
		m_currentEnergy = m_defaultEnergy;
		m_bombCount = m_defaultBombCount;
	}

	void PlayerBase::KnockBack(const KnockBackData& data) {
		// 無敵の場合無視
		if (m_isInvincible)
			return;

		m_aggriever = data.Aggriever;
		m_isDuringReturn = true;
		m_returnTimer.Reset();
		// ノックバック倍率
		float knockBackCorrection = 1.0f;
		//// アーマーが回復中でない　かつ　アーマーが0より大きい
		//if (m_currentArmorPoint > 0 && !m_isRestoreArmor) {
		//	knockBackCorrection = 1.0f;
		//}
		//else {
		//	knockBackCorrection = m_armorZeroWhenKnockBackMagnification;
		//	m_isRestoreArmor = true;
		//}
		// ダメージ判定
		switch (data.Type) {
		case KnockBackData::Category::Bullet:
			DecrementEnergy(10);
			break;
		case KnockBackData::Category::Bomb:
			DecrementEnergy(5);
			break;
		default:
			break;
		}
		GetComponent<PhysicalBehavior>()->Impact(
			data.Direction, data.Amount * knockBackCorrection);
	}

	void PlayerBase::SetActive(bool flg) {
		// 重力
		auto gravity = GetComponent<Gravity>();
		gravity->SetUpdateActive(flg);
		// モデル
		m_model.lock()->SetDrawActive(flg);
		// 当たり判定
		GetComponent<Collision>()->SetUpdateActive(flg);
		// 予測線表示
		m_predictionLine.SetActive(flg);
		m_isActive = flg;
	}

	void PlayerBase::Died() {
		m_respawnStateMachine->ChangeState(PlayerDiedState::Instance());
	}

	void PlayerBase::DiedInit() {
		// 復帰中に死んだ場合加害者に倒した通知を行う
		if (m_isDuringReturn && m_aggriever.lock() != nullptr) {
			m_aggriever.lock()->KilledPlayer();
		}
		// 復帰判定の初期化
		m_isDuringReturn = false;
		// 死亡回数を増やす
		m_deadCount++;
		// 各種パラメータを初期化
		ParameterReset();
		// 速度を0に
		GetComponent<PhysicalBehavior>()->SetVelocityZero();
		SetActive(false);
		// エフェクトと効果音の再生
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"FallSE", 0, 0.3f);
		OnRespawn();
		// 初期位置に戻る
		GetTransform()->SetPosition(m_initialPosition);
	}

	void PlayerBase::RespawnInit() {
		SetActive(true);
		m_invincibleTimer.Reset();
		m_isInvincible = true;
		GetComponent<EfkComponent>()->Play(L"Respawn");
	}

	bool PlayerBase::DecrementEnergy(float amount) {
		// 残量が減らす量より少ない場合（マイナスになる場合）
		if (m_currentEnergy < amount) {
			// 何もしない
			return false;
		}
		else {
			// 減らせる場合は減らす
			m_currentEnergy -= amount;
			return true;
		}
	}

	void PlayerBase::KnockBackEffectDrawing() {
		// GravityコンポーネントとPhysicalBehaviorコンポーネントのVelocityを
		// 取得し合成
		auto gravity = GetComponent<Gravity>()->GetGravityVelocity();
		auto totalVelocity = GetVelocity() + gravity;
		auto efkComp = GetComponent<EfkComponent>();

		if (totalVelocity.lengthSqr() > 10 * 10) {
			efkComp->Play(L"Smoke");
		}
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// アーマーを0にする
		if (keyState.m_bPressedKeyTbl['0']) {
			m_currentEnergy = 0.0f;
			Debug::GetInstance()->Log(L"Test:Energy0");
			GetComponent<EfkComponent>()->Play(L"BombPlus");
		}
		GetComponent<EfkComponent>()->SyncPosition(L"BombPlus");

		if (keyState.m_bPressedKeyTbl['1'] &&
			m_playerNumber == PlayerNumber::P1) {
			m_countKilledPlayer += 10;
			Debug::GetInstance()->Log(L"P1 +10Kill");
		}

		if (keyState.m_bPressedKeyTbl['2'] &&
			m_playerNumber == PlayerNumber::P2) {
			m_countKilledPlayer += 10;
			Debug::GetInstance()->Log(L"P2 +10Kill");
		}
		if (keyState.m_bPressedKeyTbl['3'] &&
			m_playerNumber == PlayerNumber::P3) {
			m_countKilledPlayer += 10;
			Debug::GetInstance()->Log(L"P3 +10Kill");
		}
		if (keyState.m_bPressedKeyTbl['4'] &&
			m_playerNumber == PlayerNumber::P4) {
			m_countKilledPlayer += 10;
			Debug::GetInstance()->Log(L"P4 +10Kill");
		}
		if (keyState.m_bPressedKeyTbl['5']) {
			GetComponent<EfkComponent>()->Play(L"Respawn");
		}
	}

	void PlayerBase::OnCollisionEnter(shared_ptr<GameObject>& other) {
		// 衝突したオブジェクトがプレイヤーの場合
		auto ptr = dynamic_pointer_cast<Bumper>(other);
		if (ptr) {
			auto gravity = GetComponent<Gravity>()->GetGravityVelocity();
			auto totalVelocity = GetVelocity() + gravity;
			//Debug::GetInstance()->Log(gravity);
			// ノックバック
			GetComponent<PhysicalBehavior>()->Impact(-totalVelocity * 4);
		}
	}

	// 通常時のステート
#pragma region PlayerNormalState
	shared_ptr<PlayerBase::PlayerNormalState> PlayerBase::PlayerNormalState::Instance() {
		static shared_ptr<PlayerNormalState> instance(new PlayerNormalState);
		return instance;
	}
	void PlayerBase::PlayerNormalState::Enter(const shared_ptr<PlayerBase>& Obj) {}
	void PlayerBase::PlayerNormalState::Execute(const shared_ptr<PlayerBase>& Obj) {
		Obj->NormalUpdate();
	}
	void PlayerBase::PlayerNormalState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion

	// 死亡時のステート
#pragma region PlayerDiedState
	shared_ptr<PlayerBase::PlayerDiedState> PlayerBase::PlayerDiedState::Instance() {
		static shared_ptr<PlayerDiedState> instance(new PlayerDiedState);
		return instance;
	}
	void PlayerBase::PlayerDiedState::Enter(const shared_ptr<PlayerBase>& Obj) {
		Obj->DiedInit();
		Obj->m_respawnTimer.Reset();
	}
	void PlayerBase::PlayerDiedState::Execute(const shared_ptr<PlayerBase>& Obj) {
		if (Obj->m_respawnTimer.Count())
			Obj->m_respawnStateMachine->ChangeState(PlayerNormalState::Instance());
	}
	void PlayerBase::PlayerDiedState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->RespawnInit();
	}

#pragma endregion

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
		Obj->BulletLaunch(Obj->BulletAim());
		// 爆弾モードへの遷移
		if (Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBombModeState::Instance());
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
	void PlayerBase::PlayerBombModeState::Enter(const shared_ptr<PlayerBase>& Obj) {
		Obj->m_isBombMode = true;
	}
	void PlayerBase::PlayerBombModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// 爆弾の照準
		Obj->BombAim();

		// 爆弾の残弾がある場合 and ボタンが押された場合
		if (Obj->m_bombCount > 0 &&
			Obj->m_inputData.IsFire &&
			Obj->m_bombCoolTimeTimer.IsTimeUp()) {
			Obj->m_bombCoolTimeTimer.Reset();
			// 爆弾を発射
			Obj->BombLaunch();
			// 残弾を減らす
			//Obj->m_bombCount--;
		}
		else {
			SoundManager::GetInstance()->Play(L"EmptyBombSE", 0, 0.3f);
		}
		// 爆弾モードを終了（弾モードへ遷移）
		if (!Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBase::PlayerBombModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->m_isBombMode = false;
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
			if (!Obj->m_isInput) {
				Obj->Hover();
			}
		}
		else {
			Obj->m_isInput = false;
			Obj->StopHover();
		}

		// 接地した場合
		if (Obj->m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// ジャンプステートへ遷移
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->StopHover();
	}
#pragma endregion
}