/*!
@file   PlayerBase.cpp
@brief  ƒvƒŒƒCƒ„[‚ÌÀ‘Ì
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
		m_bombAimMovingDistance(20)
	{
		m_transformData = transData;
		m_transformData.Scale *= 2.0f;
		auto rot = m_transformData.Rotation;
		m_lastFrontDirection = Vec3(sinf(rot.y), 0.0f, cosf(rot.y));
		// ˆÈ‰º‚Ìƒ^ƒO‚ğ‚ÂƒIƒuƒWƒFƒNƒg‚ğ”»’è‚©‚çœŠO
		m_groundingDecision.AddNotDecisionTag(L"Bomb");
		m_groundingDecision.AddNotDecisionTag(L"Bullet");
	}

	void PlayerBase::OnCreate() {
		// XML‚Ìƒf[ƒ^‚ğæ“¾
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		// ƒvƒŒƒCƒ„[‚ÌFî•ñ‚ğæ“¾
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/PlayerColor");
		// 4ƒvƒŒƒCƒ„[•ª‚ÌF‚ğ‹ó”’‚Å4‚Â‚Ìƒf[ƒ^‚É•ª‚¯‚é
		auto colorStr = DataExtracter::DelimitData(data, L' ');
		// ©g‚ÌƒvƒŒƒCƒ„[”Ô†‚É‰‚¶‚½Fƒf[ƒ^‚ğRGBA‚É•ª—Ş
		auto color = DataExtracter::DelimitData(colorStr[(UINT)m_playerNumber]);
		// •ª—Ş‚µ‚½‚à‚Ì‚ğCol4‚É•ÏŠ·
		m_color = DataExtracter::ColorDataExtraction(color);
		// 0`1‚É•ÏŠ·
		m_color = Utility::ConvertColorZeroToOne(m_color);

		// ƒvƒŒƒCƒ„[‚Ìƒ‚ƒfƒ‹‚ğ’Ç‰Á
		m_model = InstantiateGameObject<PlayerModel>(GetThis<PlayerBase>(), m_transformData);

		// —\‘ªü‚ÌF‚ğİ’è
		m_predictionLine.SetColor(m_color);

		// ŠŠ‚é‚æ‚¤‚È‹““®—p‚ÌƒRƒ“ƒ|[ƒlƒ“ƒg‚Æd—Í‚ğ’Ç‰Á
		AddComponent<PhysicalBehavior>();
		auto gravity = AddComponent<Gravity>();
		//auto defaultGravity = gravity->GetGravity();
		//// d—Í‚ğƒfƒtƒHƒ‹ƒg‚Ì3”{‚Éİ’è
		//gravity->SetGravity(defaultGravity * 3);
				// ŠO•”ƒtƒ@ƒCƒ‹‚©‚çƒXƒe[ƒ^ƒX‚ğ“Ç‚İ‚İ
		StatusLoad();

		// “–‚½‚è”»’è‚ğ’Ç‰Á
		AddComponent<CollisionSphere>()->SetDrawActive(false);

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Jump", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Hover", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Smoke", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale), true);
		// —‚¿‚½‚Æ‚«‚ÌƒGƒtƒFƒNƒg‚Ì‘ã‚í‚è
		efkComp->SetEffectResource(L"Explosion", TransformData(Vec3(0.0f), Vec3(1.0f, 5.0f, 1.0f)));

		// •ŠíƒXƒe[ƒgƒ}ƒVƒ“‚Ì\’z‚Æİ’è
		m_weaponStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		// ƒWƒƒƒ“ƒv•ƒzƒo[ƒXƒe[ƒgƒ}ƒVƒ“‚Ì\’z‚Æİ’è
		m_jumpAndHoverStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());

		// ƒ^ƒO‚Ì’Ç‰Á
		AddTag(L"Player");

		// Še’l‚Ì‰Šú‰»
		ParameterReset();
		m_initialPosition = GetTransform()->GetPosition();
		SoundManager::GetInstance()->InitPlayOverlap(L"HoverSE", 0.06f);
		// Ú’n”»’è‚Ìî•ñ‚ğ‰Šú‰»
		m_groundingDecision.SetRadius(GetTransform()->GetScale());
		//Debug::GetInstance()->Log(m_lastFrontDirection);
		//m_predictionLine.Update(GetTransform()->GetPosition(),
		//	GetTransform()->GetPosition() + m_lastFrontDirection * 5, PredictionLine::Type::Bullet);
	}

	void PlayerBase::OnUpdate() {
		// •œ‹A’†‚ÅÚ’n‚µ‚Ä‚¢‚é‚©‚Â
		if (m_isDuringReturn &&
			m_groundingDecision.Calculate(GetTransform()->GetPosition())) {
			// ˆê’èŠÔŒo‰ß‚µ‚½‚ç•œ‹A‚ªI—¹‚µ‚½”»’è‚É
			if (m_returnTimer.Count()) {
				m_isDuringReturn = false;
			}
		}

		// auto gameStage = GetTypeStage<GameStage>(false);
		//// Œ»İ‚ÌƒXƒe[ƒW‚ªGameStage
		// if (gameStage) {
		//	switch (gameStage->GetCurrentGameState())
		//	{
		//	case GameStage::GameState::PLAYING:
		//		// “ü—Í‚ÌXV
		//		InputUpdate();
		//		break;
		//	}
		// }

		InputUpdate();

		// ˆÚ“®ˆ—
		Move();
		// ƒeƒXƒgƒR[ƒh
		TestFanc();

		// –³“Gˆ—
		Invincible();
		// ŠeíƒXƒe[ƒgƒ}ƒVƒ“‚ÌXV
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
		// Ú’n‚µ‚Ä‚¢‚é‚Æ‚«‚¾‚¯ƒGƒlƒ‹ƒM[‚ğ‰ñ•œ
		if (m_groundingDecision.Calculate(GetTransform()->GetPosition()))
			EnergyRecovery();
		// ”š’e‚ÌƒN[ƒ‹ƒ^ƒCƒ€‚ÌXV
		m_bombCoolTimeTimer.Count();
		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÑƒGï¿½tï¿½Fï¿½Nï¿½gï¿½Ì•`ï¿½ï¿½
		KnockBackEffectDrawing();
	}

	void PlayerBase::Move() {
		auto physicalComp = GetComponent<PhysicalBehavior>();
		physicalComp->Move(m_inputData.MoveDirection, m_moveSpeed);
		auto efkComp = GetComponent<EfkComponent>();

		// ˆÚ“®‚µ‚Ä‚¢‚ÄÚ’n‚µ‚Ä‚¢‚éê‡
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
		// ƒGƒtƒFƒNƒg‚ÆŒø‰Ê‰¹‚ÌÄ¶
		GetComponent<EfkComponent>()->Play(L"Jump");
		SoundManager::GetInstance()->Play(L"JumpSE", 0, 0.3f);
	}

	void PlayerBase::Hover() {
		m_isHoverMode = true;
		auto delta = App::GetApp()->GetElapsedTime();
		// ƒGƒlƒ‹ƒM[‚ª‚È‚¢ê‡‚Íƒzƒo[‚ğ’â~
		if (!DecrementEnergy(m_energyRequiredInHover * delta)) {
			StopHover();
			return;
		}
		GetComponent<Gravity>()->SetGravityVerocityZero();

		// ƒzƒo[ƒGƒtƒFƒNƒg
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
		// ˆÊ’u‚Æ•ûŒü
		Ray ray(
			GetTransform()->GetPosition(),
			BulletAimCorrection(m_inputData.BulletAim.normalize())
		);
		// —\‘ªü‚ÍStart‚ÆEnd‚Ì2“_‚Ìî•ñ‚ª•K—v
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);
		// Æ€•ûŒü‚ğ³–Ê‚É‚µ‚ÄA³–Ê•ûŒü‚ğ•Ô‚·
		return TurnFrontToDirection(ray.Direction);
	}

	void PlayerBase::BulletLaunch(const Vec3& bulletAim) {
		if (bulletAim == Vec3(0))
			return;

		// ’e‚Ì”­Ë
		if (m_bulletTimer.Count() && m_inputData.IsFire) {
			// ƒGƒlƒ‹ƒM[‚ğg‚¦‚éê‡’e‚ğ”­Ë
			if (DecrementEnergy(m_energyRequiredInBulletLaunch)) {
				m_bulletTimer.Reset();
				InstantiateGameObject<Bullet>(GetThis<PlayerBase>(), bulletAim, m_bulletPower);
				SoundManager::GetInstance()->Play(L"ShotSE", 0, 0.3f);
			}
		}
	}

	Vec3 PlayerBase::BulletAimCorrection(const Vec3& launchDirection) {
		vector<Vec3> positions;

		// ƒvƒŒƒCƒ„[‚Ìæ“¾
		const auto& players = PlayerManager::GetInstance()->GetAllPlayer();
		for (auto player : players) {
			if (player == GetThis<PlayerBase>())
				continue;
			auto pos = player->GetTransform()->GetPosition();
			if (InViewRange(launchDirection, pos))
				positions.push_back(pos);
		}

		// ƒŠƒXƒg‚ª‹ó‚Ìê‡•â³‚µ‚È‚¢
		if (positions.size() <= 0)
			return launchDirection;

		// Å‚à©g‚É‹ß‚¢ˆÊ’u‚ğ‹‚ß‚é
		auto closestPosition = Vec3(INFINITY);
		for (auto position : positions) {
			auto direction = position - GetTransform()->GetPosition();
			if (direction.lengthSqr() < closestPosition.lengthSqr())
				closestPosition = position;
		}

		auto direction = closestPosition - GetTransform()->GetPosition();
		// yÀ•W‚ğ‡‚í‚¹‚é
		direction.y = launchDirection.y;
		return direction.normalize();
	}

	bool PlayerBase::InViewRange(const Vec3& aimDirection, const Vec3& position) {
		// ©•ª‚©‚çposition‚Ö‚ÌƒxƒNƒgƒ‹
		Vec3 direction = position - GetTransform()->GetPosition();
		// Æ€•ûŒü‚©‚çŒ©‚½targetPos‚Æ‚ÌŠp“x
		float deg = Utility::GetTwoVectorAngle(aimDirection, direction.normalize());
		// Šp“x‚ª‹–ì‚Ì”ÍˆÍ“à‚©‚Ç‚¤‚©(angle‚Í¶‰E‡‚í‚¹‚Ä‚ÌŠp“x‚È‚Ì‚Å€2)
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
		// direction‚ªVec3(0.0f)‚¾‚Á‚½‚ç‘O‰ñ‚Ì•ûŒü‚Ì‚Ü‚ÜˆÛ
		Vec3 _direction = direction != Vec3(0.0f) ? direction : m_lastFrontDirection;
		_direction.y = 0;
		// •ûŒü‚É³–Ê‚ğŒü‚¯‚é
		auto rad = atan2f(-_direction.z, _direction.x) - XM_PIDIV2;
		rot.y = rad;
		GetTransform()->SetRotation(rot);
		m_lastFrontDirection = _direction;
		return _direction;
	}

	void PlayerBase::EnergyRecovery() {
		// ƒfƒtƒHƒ‹ƒg’l‚ğ’´‚¦‚½‚ç‰ñ•œ’â~
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
		// XML‚Ìƒf[ƒ^‚ğæ“¾
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
				L"’è‹`‚³‚ê‚Ä‚¢‚È‚¢‚©–¢À‘•‚Å‚·B",
				L"switch (m_playerType)",
				L"PlayerBase::StatusLoad()");
			break;
		}
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/" + type);
		// 4ƒvƒŒƒCƒ„[•ª‚ÌF‚ğ‹ó”’‚Å4‚Â‚Ìƒf[ƒ^‚É•ª‚¯‚é
		auto statusStr = DataExtracter::DelimitData(data, L' ');
		// •¶š—ñ‚Ìƒf[ƒ^‚ğ”’l‚É•ÏŠ·
		vector<float> status;
		for (auto stat : statusStr) {
			status.push_back((float)_wtof(stat.c_str()));
		}

		// ˆÚ“®‘¬“x
		m_moveSpeed = status[0];
		// ƒWƒƒƒ“ƒv—Ê
		m_jumpVerocity = Vec3(0, status[1], 0);
		// ’e‚Ì”­Ë‚É•K—v‚ÈƒGƒlƒ‹ƒM[
		m_energyRequiredInBulletLaunch = status[2];
		// ƒzƒo[‚É•K—v‚ÈƒGƒlƒ‹ƒM[
		m_energyRequiredInHover = status[3];
		// ƒGƒlƒ‹ƒM[‚Ì‰ñ•œ‘¬“x
		m_energyRecoveryAmount = status[4];
		// ’e‚ÌˆĞ—Í
		m_bulletPower = status[5];
		// ”š’e‚ÌˆĞ—Í
		m_bombPower = status[6];
		// ’e‚Ì˜AË‘¬“x
		m_bulletTimer.SetIntervalTime(status[7], true);
		m_bombCoolTimeTimer.SetIntervalTime(status[8], true);
		auto defaultGravity = GetComponent<Gravity>()->GetGravity();
		// d—Í‚ğƒfƒtƒHƒ‹ƒg‚Ì3”{‚Éİ’è
		GetComponent<Gravity>()->SetGravity(defaultGravity * status[9]);
	}

	void PlayerBase::ParameterReset() {
		m_currentEnergy = m_defaultEnergy;
		m_bombCount = m_defaultBombCount;
	}

	void PlayerBase::KnockBack(const KnockBackData& data) {
		// –³“G‚Ìê‡–³‹
		if (m_isInvincible)
			return;

		m_aggriever = data.Aggriever;
		m_isDuringReturn = true;
		m_returnTimer.Reset();
		// ƒmƒbƒNƒoƒbƒN”{—¦
		float knockBackCorrection = 1.0f;
		//// ƒA[ƒ}[‚ª‰ñ•œ’†‚Å‚È‚¢@‚©‚Â@ƒA[ƒ}[‚ª0‚æ‚è‘å‚«‚¢
		//if (m_currentArmorPoint > 0 && !m_isRestoreArmor) {
		//	knockBackCorrection = 1.0f;
		//}
		//else {
		//	knockBackCorrection = m_armorZeroWhenKnockBackMagnification;
		//	m_isRestoreArmor = true;
		//}
		// ƒ_ƒ[ƒW”»’è
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

	void PlayerBase::Respawn() {
		// •œ‹A’†‚É€‚ñ‚¾ê‡‰ÁŠQÒ‚É“|‚µ‚½’Ê’m‚ğs‚¤
		if (m_isDuringReturn && m_aggriever.lock() != nullptr) {
			m_aggriever.lock()->KilledPlayer();
		}
		// •œ‹A”»’è‚Ì‰Šú‰»
		m_isDuringReturn = false;
		// €–S‰ñ”‚ğ‘‚â‚·
		m_deadCount++;
		// Šeíƒpƒ‰ƒ[ƒ^‚ğ‰Šú‰»
		ParameterReset();
		// ƒGƒtƒFƒNƒg‚ÆŒø‰Ê‰¹‚ÌÄ¶
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"FallSE", 0, 0.3f);
		OnRespawn();
		// ‰ŠúˆÊ’u‚É–ß‚é
		GetTransform()->SetPosition(m_initialPosition);
		m_invincibleTimer.Reset();
		m_isInvincible = true;
	}

	bool PlayerBase::DecrementEnergy(float amount) {
		// c—Ê‚ªŒ¸‚ç‚·—Ê‚æ‚è­‚È‚¢ê‡iƒ}ƒCƒiƒX‚É‚È‚éê‡j
		if (m_currentEnergy < amount) {
			// ‰½‚à‚µ‚È‚¢
			return false;
		}
		else {
			// Œ¸‚ç‚¹‚éê‡‚ÍŒ¸‚ç‚·
			m_currentEnergy -= amount;
			return true;
		}
	}

	void PlayerBase::KnockBackEffectDrawing() {
		// Gravityï¿½Rï¿½ï¿½ï¿½|ï¿½[ï¿½lï¿½ï¿½ï¿½gï¿½ï¿½PhysicalBehaviorï¿½Rï¿½ï¿½ï¿½|ï¿½[ï¿½lï¿½ï¿½ï¿½gï¿½ï¿½Velocityï¿½ï¿½
		// ï¿½æ“¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		auto gravity = GetComponent<Gravity>()->GetGravityVelocity();
		auto totalVelocity = GetVelocity() + gravity;
		auto efkComp = GetComponent<EfkComponent>();

		if (totalVelocity.lengthSqr() > 10 * 10) {
			efkComp->Play(L"Smoke");
		}
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// ƒA[ƒ}[‚ğ0‚É‚·‚é
		if (keyState.m_bPressedKeyTbl['0']) {
			m_currentEnergy = 0.0f;
			Debug::GetInstance()->Log(L"Test:Energy0");
		}

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
	}

	void PlayerBase::OnCollisionEnter(shared_ptr<GameObject>& other) {
		// Õ“Ë‚µ‚½ƒIƒuƒWƒFƒNƒg‚ªƒvƒŒƒCƒ„[‚Ìê‡
		auto ptr = dynamic_pointer_cast<Bumper>(other);
		if (ptr) {
			auto gravity = GetComponent<Gravity>()->GetGravityVelocity();
			auto totalVelocity = GetVelocity() + gravity;
			//Debug::GetInstance()->Log(gravity);
			// ƒmƒbƒNƒoƒbƒN
			GetComponent<PhysicalBehavior>()->Impact(-totalVelocity * 4);
		}
	}

	// •Ší—pƒXƒe[ƒg
	// ’e‚ÌÆ€‚â”­Ëó‘ÔiƒfƒtƒHƒ‹ƒgj
#pragma region PlayerBulletModeState
	shared_ptr<PlayerBase::PlayerBulletModeState> PlayerBase::PlayerBulletModeState::Instance() {
		static shared_ptr<PlayerBulletModeState> instance(new PlayerBulletModeState);
		return instance;
	}
	void PlayerBase::PlayerBulletModeState::Enter(const shared_ptr<PlayerBase>& Obj) {}
	void PlayerBase::PlayerBulletModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// ’e‚ÌÆ€‚Æ”­Ë
		Obj->BulletLaunch(Obj->BulletAim());
		// ”š’eƒ‚[ƒh‚Ö‚Ì‘JˆÚ
		if (Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBombModeState::Instance());
		}
	}
	void PlayerBase::PlayerBulletModeState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion

	// ”š’e‚ÌÆ€‚â”­Ëó‘Ô
#pragma region PlayerBombModeState
	shared_ptr<PlayerBase::PlayerBombModeState> PlayerBase::PlayerBombModeState::Instance() {
		static shared_ptr<PlayerBombModeState> instance(new PlayerBombModeState);
		return instance;
	}
	void PlayerBase::PlayerBombModeState::Enter(const shared_ptr<PlayerBase>& Obj) {
		Obj->m_isBombMode = true;
	}
	void PlayerBase::PlayerBombModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// ”š’e‚ÌÆ€
		Obj->BombAim();

		// ”š’e‚Ìc’e‚ª‚ ‚éê‡ and ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½ê‡
		if (Obj->m_bombCount > 0 &&
			Obj->m_inputData.IsFire &&
			Obj->m_bombCoolTimeTimer.IsTimeUp()) {
			Obj->m_bombCoolTimeTimer.Reset();
			// ”š’e‚ğ”­Ë
			Obj->BombLaunch();
			// c’e‚ğŒ¸‚ç‚·
			//Obj->m_bombCount--;
		}
		else {
			SoundManager::GetInstance()->Play(L"EmptyBombSE", 0, 0.3f);
		}
		// ”š’eƒ‚[ƒh‚ğI—¹i’eƒ‚[ƒh‚Ö‘JˆÚj
		if (!Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBase::PlayerBombModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->m_isBombMode = false;
	}
#pragma endregion

	// ƒWƒƒƒ“ƒv
#pragma region PlayerJumpState
	shared_ptr<PlayerBase::PlayerJumpState> PlayerBase::PlayerJumpState::Instance() {
		static shared_ptr<PlayerJumpState> instance(new PlayerJumpState);
		return instance;
	}
	void PlayerBase::PlayerJumpState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// ‘JˆÚ‚É“ü—Í‚ª‚ ‚éê‡
		if (Obj->m_inputData.IsJumpOrHover) {
			// ƒtƒ‰ƒO‚ğ—§‚Ä‚é
			Obj->m_isInput = true;
		}
	}
	void PlayerBase::PlayerJumpState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// “ü—Í‚ª‚ ‚éê‡
		if (Obj->m_inputData.IsJumpOrHover) {
			// ‘JˆÚ‚É“ü—Í‚ª‚ ‚Á‚½ê‡‚ÍƒWƒƒƒ“ƒv‚µ‚È‚¢
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
	// ƒzƒo[
#pragma region PlayerHoverState
	shared_ptr<PlayerBase::PlayerHoverState> PlayerBase::PlayerHoverState::Instance() {
		static shared_ptr<PlayerHoverState> instance(new PlayerHoverState);
		return instance;
	}
	void PlayerBase::PlayerHoverState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// ‘JˆÚ‚É“ü—Í‚ª‚ ‚éê‡
		if (Obj->m_inputData.IsJumpOrHover) {
			// ƒtƒ‰ƒO‚ğ—§‚Ä‚é
			Obj->m_isInput = true;
		}
	}
	void PlayerBase::PlayerHoverState::Execute(const shared_ptr<PlayerBase>& Obj) {
		if (Obj->m_inputData.IsJumpOrHover) {
			// ‘JˆÚ‚É“ü—Í‚ª‚ ‚Á‚½ê‡ƒzƒo[‚ğs‚í‚È‚¢iˆê“x—£‚·•K—v‚ª‚ ‚éj
			if (!Obj->m_isInput) {
				Obj->Hover();
			}
		}
		else {
			Obj->m_isInput = false;
			Obj->StopHover();
		}

		// Ú’n‚µ‚½ê‡
		if (Obj->m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// ƒWƒƒƒ“ƒvƒXƒe[ƒg‚Ö‘JˆÚ
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->StopHover();
	}
#pragma endregion
}