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
		m_hoverTime(2.0f), m_currentHoverTime(m_hoverTime),
		m_defaultArmorPoint(100.0f), m_currentArmorPoint(m_defaultArmorPoint),
		m_bulletTimer(0.1f, true), m_armorRecoveryTimer(2.0f),
		m_isRestoreArmor(false), m_isInput(false), m_playerNumber(playerNumber),
		m_bombReload(1.0f), m_defaultBombCount(5), m_correctAngle(40.0f),
		m_isDuringReturn(false), m_groundingDecision(), m_countKilledPlayer(0),
		m_returnTimer(0.5f), m_lastFrontDirection(Vec3(0.0f)), m_smokeTimer(0.2f),
		m_deadCount(0), m_invincibleTimer(3.0f, true), m_isInvincible(false),
		m_defaultSkillEnergy(100.0f), m_currentSkillEnergy(0.0f)
	{
		m_transformData = transData;
		m_transformData.Scale *= 2.0f;
		auto rot = m_transformData.Rotation;
		m_lastFrontDirection = Vec3(cosf(rot.y), 0.0f, sinf(rot.y));
		// �ȉ��̃^�O�����I�u�W�F�N�g�𔻒肩�珜�O
		m_groundingDecision.AddNotDecisionTag(L"Bomb");
		m_groundingDecision.AddNotDecisionTag(L"Bullet");
	}

	void PlayerBase::OnCreate() {
		// XML�̃f�[�^���擾
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		auto node = xmlData->GetSelectSingleNode(L"Player/PlayerColor");
		if (!node) {
			throw BaseException(
				L"Player/PlayerColor��������܂���",
				L"if (!node)",
				L"PlayerBase::OnCreate()");
		}
		// �v���C���[�̐F�����擾
		wstring data = XmlDocReader::GetText(node);
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
		auto defaultGravity = gravity->GetGravity();
		// �d�͂��f�t�H���g��2�{�ɐݒ�
		gravity->SetGravity(defaultGravity * 2.0f);
		// �����蔻���ǉ�
		AddComponent<CollisionSphere>()->SetDrawActive(false);

		auto efkComp = AddComponent<EfkComponent>();
		efkComp->SetEffectResource(L"Jump", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Hover", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale));
		efkComp->SetEffectResource(L"Smoke", TransformData(Vec3(0.0f, -0.5f, 0.0f), m_transformData.Scale), true);
		// �������Ƃ��̃G�t�F�N�g�̑���
		efkComp->SetEffectResource(L"Explosion", TransformData(Vec3(0.0f), Vec3(1.0f, 5.0f, 1.0f)));

		// ����X�e�[�g�}�V���̍\�z�Ɛݒ�
		m_weaponStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		// �W�����v���z�o�[�X�e�[�g�}�V���̍\�z�Ɛݒ�
		m_jumpAndHoverStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());

		// �^�O�̒ǉ�
		AddTag(L"Player");

		// �e�l�̏�����
		m_currentArmorPoint = m_defaultArmorPoint;
		m_currentHoverTime = m_hoverTime;
		m_bombCount = m_defaultBombCount;
		m_initialPosition = GetTransform()->GetPosition();
		SoundManager::GetInstance()->InitPlayOverlap(L"HoverSE", 0.06f);
		// �ڒn����̏���������
		m_groundingDecision.SetRadius(GetTransform()->GetScale());
	}

	void PlayerBase::OnUpdate() {
		// ���A���Őڒn���Ă��邩��
		if (m_isDuringReturn &&
			m_groundingDecision.Calculate(GetTransform()->GetPosition())) {
			// ��莞�Ԍo�߂����畜�A���I�����������
			if (m_returnTimer.Count()) {
				m_isDuringReturn = false;
			}
		}

		// ���͂̍X�V
		InputUpdate();
		// �ړ�����
		Move();
		// �e�X�g�R�[�h
		TestFanc();
		// ���e�̃����[�h
		BombReload();
		// ���G����
		Invincible();
		// �e��X�e�[�g�}�V���̍X�V
		m_weaponStateMachine->Update();
		m_jumpAndHoverStateMachine->Update();
		// �A�[�}�[�񕜃t���O��true�̏ꍇ
		if (m_isRestoreArmor)
			// �A�[�}�[����
			ArmorRecovery();
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
		// �z�o�[�\���Ԃ�0�ȏ�̏ꍇ�̓z�o�[
		if (m_currentHoverTime < 0.0f) {
			StopHover();
			return;
		}
		GetComponent<Gravity>()->SetGravityVerocityZero();
		m_currentHoverTime -= App::GetApp()->GetElapsedTime();

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

	void PlayerBase::HoverTimeRecovery() {
		if (m_hoverTime > m_currentHoverTime) {
			m_currentHoverTime += App::GetApp()->GetElapsedTime();
		}
		else {
			m_currentHoverTime = m_hoverTime;
		}
	}

	void PlayerBase::SpecialSkill() {
		// GetStage()->AddGameObject<SpecialCamera>();
		SpecialSkillManager::GetInstance()->ActiveSpecialSkill(m_playerType, GetThis<PlayerBase>());
	}

	void PlayerBase::BulletAimAndLaunch() {
		auto userPosition = GetTransform()->GetPosition();
		auto bulletAim = BulletAimCorrection(m_inputData.BulletAim.normalize());

		Ray ray(userPosition, bulletAim);
		// �\������Start��End��2�_�̏�񂪕K�v
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);

		// �e�̔���
		if (bulletAim != Vec3(0.0f) && m_bulletTimer.Count()) {
			m_bulletTimer.Reset();
			InstantiateGameObject<Bullet>(GetThis<PlayerBase>(), ray);
			SoundManager::GetInstance()->Play(L"ShotSE", 0, 0.3f);
		}
		TurnFrontToDirection(ray.Direction);
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
		m_bombPoint += m_inputData.BombAim * delta * 20.0f;
		m_predictionLine.Update(GetTransform()->GetPosition(), m_bombPoint, PredictionLine::Type::Bomb);
		TurnFrontToDirection(m_bombPoint - GetTransform()->GetPosition());
	}

	void PlayerBase::BombReload() {
		// ���݂̔��e�̐����ő吔�ȏ�̏ꍇ�͉������Ȃ�
		if (m_bombCount < m_defaultBombCount) {
			// ���̎��Ԃ��o�߂�����
			if (m_bombReload.Count()) {
				// �c�e�𑝂₵�A�^�C�}�[�����Z�b�g
				m_bombCount++;
				m_bombReload.Reset();
			}
		}
	}

	void PlayerBase::BombLaunch() {
		InstantiateGameObject<Bomb>(GetThis<PlayerBase>(),
			m_predictionLine, GetTransform()->GetPosition(), m_bombPoint);
		SoundManager::GetInstance()->Play(L"ThrowBombSE", 0, 0.3f);
	}

	void PlayerBase::TurnFrontToDirection(const Vec3& direction) {
		Vec3 rot(0.0f);
		// direction��Vec3(0.0f)��������O��̕����̂܂܈ێ�
		Vec3 _direction = direction != Vec3(0.0f) ? direction : m_lastFrontDirection;
		// �����ɐ��ʂ�������
		auto rad = atan2f(-_direction.z, _direction.x) - XM_PIDIV2;
		rot.y = rad;
		GetTransform()->SetRotation(rot);
		m_lastFrontDirection = _direction;
	}

	void PlayerBase::ArmorRecovery() {
		// �A�[�}�[��0�ɂȂ��Ă����莞�Ԍ�ɉ�
		if (!m_armorRecoveryTimer.Count())
			return;

		// m_defaultArmorPoint�𒴂�����񕜒�~
		if (m_currentArmorPoint >= m_defaultArmorPoint) {
			m_currentArmorPoint = m_defaultArmorPoint;
			m_isRestoreArmor = false;
			m_armorRecoveryTimer.Reset();
		}
		m_currentArmorPoint += 10.0f * App::GetApp()->GetElapsedTime();
	}

	void PlayerBase::StopHover() {
		m_isHoverMode = false;
		GetComponent<EfkComponent>()->Stop(L"Hover");
		OnStopHover();
	}

	void PlayerBase::KnockBack(const KnockBackData& data) {
		// ���G�̏ꍇ����
		if (m_isInvincible)
			return;

		m_aggriever = data.Aggriever;
		m_isDuringReturn = true;
		m_returnTimer.Reset();
		// �m�b�N�o�b�N�{��
		float knockBackCorrection;
		// �A�[�}�[���񕜒��łȂ��@���@�A�[�}�[��0���傫��
		if (m_currentArmorPoint > 0 && !m_isRestoreArmor) {
			knockBackCorrection = 1.0f;
		}
		else {
			knockBackCorrection = 5.0f;
			m_isRestoreArmor = true;
		}
		// �_���[�W����
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
		AddEnergy(5.0f);
		GetComponent<PhysicalBehavior>()->Impact(
			data.Direction, data.Amount * knockBackCorrection);
	}

	void PlayerBase::Respawn() {
		// ���A���Ɏ��񂾏ꍇ���Q�҂ɓ|�����ʒm���s��
		if (m_isDuringReturn && m_aggriever.lock() != nullptr) {
			m_aggriever.lock()->KilledPlayer();
		}
		// ���A����̏�����
		m_isDuringReturn = false;
		// ���S�񐔂𑝂₷
		m_deadCount++;
		// �e��p�����[�^��������
		m_currentArmorPoint = m_defaultArmorPoint;
		m_currentHoverTime = m_hoverTime;
		m_bombCount = m_defaultBombCount;
		m_bombReload.Reset();
		// �G�t�F�N�g�ƌ��ʉ��̍Đ�
		GetComponent<EfkComponent>()->Play(L"Explosion");
		SoundManager::GetInstance()->Play(L"FallSE", 0, 0.3f);
		OnRespawn();
		// �����ʒu�ɖ߂�
		GetTransform()->SetPosition(m_initialPosition);
		m_invincibleTimer.Reset();
		m_isInvincible = true;
	}

	void PlayerBase::AddEnergy(float amount) {
		m_currentSkillEnergy += amount;
		// �f�t�H���g�𒴂���ꍇ�f�t�H���g�l��
		if (m_currentSkillEnergy > m_defaultSkillEnergy)
			m_currentSkillEnergy = m_defaultSkillEnergy;
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// �A�[�}�[��0�ɂ���
		if (keyState.m_bPressedKeyTbl['0']) {
			m_currentArmorPoint = 0.0f;
			m_isRestoreArmor = true;
			Debug::GetInstance()->Log(L"Test:Armor0");
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
		Obj->BulletAimAndLaunch();
		// ���e���[�h�ւ̑J��
		if (Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBombModeState::Instance());
		}
		// �K�E�Z���[�h�ւ̑J��
		if (Obj->m_inputData.IsInvokeSpecialSkill) {
			// �����\�ȏꍇ�̂ݑJ��
			if (SpecialSkillManager::GetInstance()->IsInvocable() &&
				Obj->m_defaultSkillEnergy == Obj->m_currentSkillEnergy)
				Obj->m_weaponStateMachine->ChangeState(PlayerSpecialSkillModeState::Instance());
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
		// ���e���[�h���I���i�e���[�h�֑J�ځj
		if (!Obj->m_inputData.IsSwitchBombMode) {
			Obj->m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
		}
	}
	void PlayerBase::PlayerBombModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
		// ���e�̎c�e������ꍇ
		if (Obj->m_bombCount > 0) {
			// �e���[�h�֑J�ڎ��ɔ��e�𔭎�
			Obj->BombLaunch();
			// �c�e�����炷
			Obj->m_bombCount--;
		}
		else {
			SoundManager::GetInstance()->Play(L"EmptyBombSE", 0, 0.3f);
		}
		Obj->m_isBombMode = false;
	}
#pragma endregion

	// �K�E�Z�������
#pragma region PlayerSpecialSkillModeState
	shared_ptr<PlayerBase::PlayerSpecialSkillModeState> PlayerBase::PlayerSpecialSkillModeState::Instance() {
		static shared_ptr<PlayerSpecialSkillModeState> instance(new PlayerSpecialSkillModeState);
		return instance;
	}
	void PlayerBase::PlayerSpecialSkillModeState::Enter(const shared_ptr<PlayerBase>& Obj) {
		Obj->SpecialSkill();
		Obj->m_currentSkillEnergy = 0;
	}
	void PlayerBase::PlayerSpecialSkillModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
		// �I��������
		if (SpecialSkillManager::GetInstance()->IsEnded())
			Obj->m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());
	}
	void PlayerBase::PlayerSpecialSkillModeState::Exit(const shared_ptr<PlayerBase>& Obj) {	}
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
		// �z�o�[�\���ԉ�
		Obj->HoverTimeRecovery();
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