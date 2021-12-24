/*!
@file   PlayerBase.cpp
@brief  �v���C���[�̎���
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
		// �ȉ��̃^�O�����I�u�W�F�N�g�𔻒肩�珜�O
		m_groundingDecision.AddNotDecisionTag(L"Bomb");
		m_groundingDecision.AddNotDecisionTag(L"Bullet");
	}

	void PlayerBase::OnCreate() {
		// XML�̃f�[�^���擾
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		// �v���C���[�̐F�����擾
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/PlayerColor");
		// 4�v���C���[���̐F���󔒂�4�̃f�[�^�ɕ�����
		auto colorStr = DataExtracter::DelimitData(data, L' ');
		// ���g�̃v���C���[�ԍ��ɉ������F�f�[�^��RGBA�ɕ���
		auto color = DataExtracter::DelimitData(colorStr[(UINT)m_playerNumber]);
		// ���ނ������̂�Col4�ɕϊ�
		m_color = DataExtracter::ColorDataExtraction(color);
		// 0�`1�ɕϊ�
		m_color = Utility::ConvertColorZeroToOne(m_color);

		// �v���C���[�̃��f����ǉ�
		m_model = InstantiateGameObject<PlayerModel>(GetThis<PlayerBase>(), m_transformData);

		// �\�����̐F��ݒ�
		m_predictionLine.SetColor(m_color);

		// ����悤�ȋ����p�̃R���|�[�l���g�Əd�͂�ǉ�
		AddComponent<PhysicalBehavior>();
		auto gravity = AddComponent<Gravity>();
		//auto defaultGravity = gravity->GetGravity();
		//// �d�͂��f�t�H���g��3�{�ɐݒ�
		//gravity->SetGravity(defaultGravity * 3);
				// �O���t�@�C������X�e�[�^�X��ǂݍ���
		StatusLoad();

		// �����蔻���ǉ�
		AddComponent<CollisionSphere>()->SetDrawActive(false);

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Jump", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Hover", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Smoke", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale), true);
		efkComp->SetEffectResource(L"BombPlus", TransformData(Vec3(0), m_transformData.Scale));
		efkComp->SetEffectResource(L"Respawn", TransformData(Vec3(0.0f, -0.5f, 0.0f)));
		// �������Ƃ��̃G�t�F�N�g�̑���
		efkComp->SetEffectResource(L"Explosion", TransformData(Vec3(0.0f), Vec3(1.0f, 5.0f, 1.0f)));

		// ����X�e�[�g�}�V���̍\�z�Ɛݒ�
		m_weaponStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		// �W�����v���z�o�[�X�e�[�g�}�V���̍\�z�Ɛݒ�
		m_jumpAndHoverStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
		// ���X�|�[���p�X�e�[�g�}�V���̍\�z�Ɛݒ�
		m_respawnStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_respawnStateMachine->ChangeState(PlayerNormalState::Instance());

		// �^�O�̒ǉ�
		AddTag(L"Player");

		// �e�l�̏�����
		ParameterReset();
		m_initialPosition = GetTransform()->GetPosition();
		SoundManager::GetInstance()->InitPlayOverlap(L"HoverSE", 0.06f);
		// �ڒn����̏���������
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
		// ���A���Őڒn���Ă��邩��
		if (m_isDuringReturn &&
			m_groundingDecision.Calculate(GetTransform()->GetPosition())) {
			// ��莞�Ԍo�߂����畜�A���I�����������
			if (m_returnTimer.Count()) {
				m_isDuringReturn = false;
			}
		}

		// auto gameStage = GetTypeStage<GameStage>(false);
		//// ���݂̃X�e�[�W��GameStage
		// if (gameStage) {
		//	switch (gameStage->GetCurrentGameState())
		//	{
		//	case GameStage::GameState::PLAYING:
		//		// ���͂̍X�V
		//		InputUpdate();
		//		break;
		//	}
		// }

		InputUpdate();

		// �ړ�����
		Move();
		// �e�X�g�R�[�h
		TestFanc();

		// ���G����
		Invincible();
		// �e��X�e�[�g�}�V���̍X�V
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
		// �ڒn���Ă���Ƃ������G�l���M�[����
		if (m_groundingDecision.Calculate(GetTransform()->GetPosition()))
			EnergyRecovery();
		// ���e�̃N�[���^�C���̍X�V
		m_bombCoolTimeTimer.Count();
		// ������уG�t�F�N�g�̕`��
		KnockBackEffectDrawing();
	}

	void PlayerBase::Move() {
		auto physicalComp = GetComponent<PhysicalBehavior>();
		physicalComp->Move(m_inputData.MoveDirection, m_moveSpeed);
		auto efkComp = GetComponent<EfkComponent>();

		// �ړ����Ă��Đڒn���Ă���ꍇ
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
		// �G�t�F�N�g�ƌ��ʉ��̍Đ�
		GetComponent<EfkComponent>()->Play(L"Jump");
		SoundManager::GetInstance()->Play(L"JumpSE", 0, 0.3f);
	}

	void PlayerBase::Hover() {
		m_isHoverMode = true;
		auto delta = App::GetApp()->GetElapsedTime();
		// �G�l���M�[���Ȃ��ꍇ�̓z�o�[���~
		if (!DecrementEnergy(m_energyRequiredInHover * delta)) {
			StopHover();
			return;
		}
		GetComponent<Gravity>()->SetGravityVerocityZero();

		// �z�o�[�G�t�F�N�g
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
		// �ʒu�ƕ���
		Ray ray(
			GetTransform()->GetPosition(),
			BulletAimCorrection(m_inputData.BulletAim.normalize())
		);
		// �\������Start��End��2�_�̏�񂪕K�v
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);
		// �Ə������𐳖ʂɂ��āA���ʕ�����Ԃ�
		return TurnFrontToDirection(ray.Direction);
	}

	void PlayerBase::BulletLaunch(const Vec3& bulletAim) {
		if (bulletAim == Vec3(0))
			return;

		// �e�̔���
		if (m_bulletTimer.Count() && m_inputData.IsFire) {
			// �G�l���M�[���g����ꍇ�e�𔭎�
			if (DecrementEnergy(m_energyRequiredInBulletLaunch)) {
				m_bulletTimer.Reset();
				InstantiateGameObject<Bullet>(GetThis<PlayerBase>(), bulletAim, m_bulletPower);
				SoundManager::GetInstance()->Play(L"ShotSE", 0, 0.3f);
			}
		}
	}

	Vec3 PlayerBase::BulletAimCorrection(const Vec3& launchDirection) {
		vector<Vec3> positions;

		// �v���C���[�̎擾
		const auto& players = PlayerManager::GetInstance()->GetAllPlayer();
		for (auto player : players) {
			if (player == GetThis<PlayerBase>())
				continue;
			auto pos = player->GetTransform()->GetPosition();
			if (InViewRange(launchDirection, pos))
				positions.push_back(pos);
		}

		// ���X�g����̏ꍇ�␳���Ȃ�
		if (positions.size() <= 0)
			return launchDirection;

		// �ł����g�ɋ߂��ʒu�����߂�
		auto closestPosition = Vec3(INFINITY);
		for (auto position : positions) {
			auto direction = position - GetTransform()->GetPosition();
			if (direction.lengthSqr() < closestPosition.lengthSqr())
				closestPosition = position;
		}

		auto direction = closestPosition - GetTransform()->GetPosition();
		// y���W�����킹��
		direction.y = launchDirection.y;
		return direction.normalize();
	}

	bool PlayerBase::InViewRange(const Vec3& aimDirection, const Vec3& position) {
		// ��������position�ւ̃x�N�g��
		Vec3 direction = position - GetTransform()->GetPosition();
		// �Ə��������猩��targetPos�Ƃ̊p�x
		float deg = Utility::GetTwoVectorAngle(aimDirection, direction.normalize());
		// �p�x������͈͓̔����ǂ���(angle�͍��E���킹�Ă̊p�x�Ȃ̂Ł�2)
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
		// direction��Vec3(0.0f)��������O��̕����̂܂܈ێ�
		Vec3 _direction = direction != Vec3(0.0f) ? direction : m_lastFrontDirection;
		_direction.y = 0;
		// �����ɐ��ʂ�������
		auto rad = atan2f(-_direction.z, _direction.x) - XM_PIDIV2;
		rot.y = rad;
		GetTransform()->SetRotation(rot);
		m_lastFrontDirection = _direction;
		return _direction;
	}

	void PlayerBase::EnergyRecovery() {
		// �f�t�H���g�l�𒴂�����񕜒�~
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
		// XML�̃f�[�^���擾
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
				L"��`����Ă��Ȃ����������ł��B",
				L"switch (m_playerType)",
				L"PlayerBase::StatusLoad()");
			break;
		}
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/" + type);
		// 4�v���C���[���̐F���󔒂�4�̃f�[�^�ɕ�����
		auto statusStr = DataExtracter::DelimitData(data, L' ');
		// ������̃f�[�^�𐔒l�ɕϊ�
		vector<float> status;
		for (auto stat : statusStr) {
			status.push_back((float)_wtof(stat.c_str()));
		}

		// �ړ����x
		m_moveSpeed = status[0];
		// �W�����v��
		m_jumpVerocity = Vec3(0, status[1], 0);
		// �e�̔��˂ɕK�v�ȃG�l���M�[
		m_energyRequiredInBulletLaunch = status[2];
		// �z�o�[�ɕK�v�ȃG�l���M�[
		m_energyRequiredInHover = status[3];
		// �G�l���M�[�̉񕜑��x
		m_energyRecoveryAmount = status[4];
		// �e�̈З�
		m_bulletPower = status[5];
		// ���e�̈З�
		m_bombPower = status[6];
		// �e�̘A�ˑ��x
		m_bulletTimer.SetIntervalTime(status[7], true);
		m_bombCoolTimeTimer.SetIntervalTime(status[8], true);
		auto defaultGravity = GetComponent<Gravity>()->GetGravity();
		// �d�͂��f�t�H���g��3�{�ɐݒ�
		GetComponent<Gravity>()->SetGravity(defaultGravity * status[9]);
	}

	void PlayerBase::ParameterReset() {
		m_currentEnergy = m_defaultEnergy;
		m_bombCount = m_defaultBombCount;
	}

	void PlayerBase::KnockBack(const KnockBackData& data) {
		// ���G�̏ꍇ����
		if (m_isInvincible)
			return;

		m_aggriever = data.Aggriever;
		m_isDuringReturn = true;
		m_returnTimer.Reset();
		// �m�b�N�o�b�N�{��
		float knockBackCorrection = 1.0f;
		//// �A�[�}�[���񕜒��łȂ��@���@�A�[�}�[��0���傫��
		//if (m_currentArmorPoint > 0 && !m_isRestoreArmor) {
		//	knockBackCorrection = 1.0f;
		//}
		//else {
		//	knockBackCorrection = m_armorZeroWhenKnockBackMagnification;
		//	m_isRestoreArmor = true;
		//}
		// �_���[�W����
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
		// �d��
		auto gravity = GetComponent<Gravity>();
		gravity->SetUpdateActive(flg);
		// ���f��
		m_model.lock()->SetDrawActive(flg);
		// �����蔻��
		GetComponent<Collision>()->SetUpdateActive(flg);
		// �\�����\��
		m_predictionLine.SetActive(flg);
		m_isActive = flg;
	}

	void PlayerBase::Died() {
		m_respawnStateMachine->ChangeState(PlayerDiedState::Instance());
	}

	void PlayerBase::DiedInit() {
		// ���A���Ɏ��񂾏ꍇ���Q�҂ɓ|�����ʒm���s��
		if (m_isDuringReturn && m_aggriever.lock() != nullptr) {
			m_aggriever.lock()->KilledPlayer();
		}
		// ���A����̏�����
		m_isDuringReturn = false;
		// ���S�񐔂𑝂₷
		m_deadCount++;
		// �e��p�����[�^��������
		ParameterReset();
		// ���x��0��
		GetComponent<PhysicalBehavior>()->SetVelocityZero();
		SetActive(false);
		// �G�t�F�N�g�ƌ��ʉ��̍Đ�
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"FallSE", 0, 0.3f);
		OnRespawn();
		// �����ʒu�ɖ߂�
		GetTransform()->SetPosition(m_initialPosition);
	}

	void PlayerBase::RespawnInit() {
		SetActive(true);
		m_invincibleTimer.Reset();
		m_isInvincible = true;
		GetComponent<EfkComponent>()->Play(L"Respawn");
	}

	bool PlayerBase::DecrementEnergy(float amount) {
		// �c�ʂ����炷�ʂ�菭�Ȃ��ꍇ�i�}�C�i�X�ɂȂ�ꍇ�j
		if (m_currentEnergy < amount) {
			// �������Ȃ�
			return false;
		}
		else {
			// ���点��ꍇ�͌��炷
			m_currentEnergy -= amount;
			return true;
		}
	}

	void PlayerBase::KnockBackEffectDrawing() {
		// Gravity�R���|�[�l���g��PhysicalBehavior�R���|�[�l���g��Velocity��
		// �擾������
		auto gravity = GetComponent<Gravity>()->GetGravityVelocity();
		auto totalVelocity = GetVelocity() + gravity;
		auto efkComp = GetComponent<EfkComponent>();

		if (totalVelocity.lengthSqr() > 10 * 10) {
			efkComp->Play(L"Smoke");
		}
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// �A�[�}�[��0�ɂ���
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
		// �Փ˂����I�u�W�F�N�g���v���C���[�̏ꍇ
		auto ptr = dynamic_pointer_cast<Bumper>(other);
		if (ptr) {
			auto gravity = GetComponent<Gravity>()->GetGravityVelocity();
			auto totalVelocity = GetVelocity() + gravity;
			//Debug::GetInstance()->Log(gravity);
			// �m�b�N�o�b�N
			GetComponent<PhysicalBehavior>()->Impact(-totalVelocity * 4);
		}
	}

	// �ʏ펞�̃X�e�[�g
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

	// ���S���̃X�e�[�g
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

	// ����p�X�e�[�g
	// �e�̏Ə��┭�ˏ�ԁi�f�t�H���g�j
#pragma region PlayerBulletModeState
	shared_ptr<PlayerBase::PlayerBulletModeState> PlayerBase::PlayerBulletModeState::Instance() {
		static shared_ptr<PlayerBulletModeState> instance(new PlayerBulletModeState);
		return instance;
	}
	void PlayerBase::PlayerBulletModeState::Enter(const shared_ptr<PlayerBase>& Obj) {}
	void PlayerBase::PlayerBulletModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// �e�̏Ə��Ɣ���
		Obj->BulletLaunch(Obj->BulletAim());
		// ���e���[�h�ւ̑J��
		if (Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBombModeState::Instance());
		}
	}
	void PlayerBase::PlayerBulletModeState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion

	// ���e�̏Ə��┭�ˏ��
#pragma region PlayerBombModeState
	shared_ptr<PlayerBase::PlayerBombModeState> PlayerBase::PlayerBombModeState::Instance() {
		static shared_ptr<PlayerBombModeState> instance(new PlayerBombModeState);
		return instance;
	}
	void PlayerBase::PlayerBombModeState::Enter(const shared_ptr<PlayerBase>& Obj) {
		Obj->m_isBombMode = true;
	}
	void PlayerBase::PlayerBombModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// ���e�̏Ə�
		Obj->BombAim();

		// ���e�̎c�e������ꍇ and �{�^���������ꂽ�ꍇ
		if (Obj->m_bombCount > 0 &&
			Obj->m_inputData.IsFire &&
			Obj->m_bombCoolTimeTimer.IsTimeUp()) {
			Obj->m_bombCoolTimeTimer.Reset();
			// ���e�𔭎�
			Obj->BombLaunch();
			// �c�e�����炷
			//Obj->m_bombCount--;
		}
		else {
			SoundManager::GetInstance()->Play(L"EmptyBombSE", 0, 0.3f);
		}
		// ���e���[�h���I���i�e���[�h�֑J�ځj
		if (!Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBase::PlayerBombModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->m_isBombMode = false;
	}
#pragma endregion

	// �W�����v
#pragma region PlayerJumpState
	shared_ptr<PlayerBase::PlayerJumpState> PlayerBase::PlayerJumpState::Instance() {
		static shared_ptr<PlayerJumpState> instance(new PlayerJumpState);
		return instance;
	}
	void PlayerBase::PlayerJumpState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// �J�ڎ��ɓ��͂�����ꍇ
		if (Obj->m_inputData.IsJumpOrHover) {
			// �t���O�𗧂Ă�
			Obj->m_isInput = true;
		}
	}
	void PlayerBase::PlayerJumpState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// ���͂�����ꍇ
		if (Obj->m_inputData.IsJumpOrHover) {
			// �J�ڎ��ɓ��͂��������ꍇ�̓W�����v���Ȃ�
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
	// �z�o�[
#pragma region PlayerHoverState
	shared_ptr<PlayerBase::PlayerHoverState> PlayerBase::PlayerHoverState::Instance() {
		static shared_ptr<PlayerHoverState> instance(new PlayerHoverState);
		return instance;
	}
	void PlayerBase::PlayerHoverState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// �J�ڎ��ɓ��͂�����ꍇ
		if (Obj->m_inputData.IsJumpOrHover) {
			// �t���O�𗧂Ă�
			Obj->m_isInput = true;
		}
	}
	void PlayerBase::PlayerHoverState::Execute(const shared_ptr<PlayerBase>& Obj) {
		if (Obj->m_inputData.IsJumpOrHover) {
			// �J�ڎ��ɓ��͂��������ꍇ�z�o�[���s��Ȃ��i��x�����K�v������j
			if (!Obj->m_isInput) {
				Obj->Hover();
			}
		}
		else {
			Obj->m_isInput = false;
			Obj->StopHover();
		}

		// �ڒn�����ꍇ
		if (Obj->m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// �W�����v�X�e�[�g�֑J��
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {
		Obj->StopHover();
	}
#pragma endregion
}