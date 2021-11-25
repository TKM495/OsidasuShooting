/*!
@file   PlayerBase.cpp
@brief  �v���C���[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerBase::OnCreate() {
		// �`��R���|�[�l���g�̒ǉ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetOwnShadowActive(true);

		// �e�̒ǉ�
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_SPHERE");

		// ����悤�ȋ����p�̃R���|�[�l���g�Əd�͂�ǉ�
		AddComponent<PhysicalBehavior>();
		AddComponent<Gravity>();
		// �����蔻���ǉ�
		AddComponent<CollisionSphere>();

		// ����X�e�[�g�}�V���̍\�z
		m_weaponStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		// ����̏����X�e�[�g�̐ݒ�
		m_weaponStateMachine->ChangeState(PlayerBulletModeState::Instance());

		// �W�����v���z�o�[
		m_jumpAndHoverStateMachine.reset(new StateMachine<PlayerBase>(GetThis<PlayerBase>()));
		m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());

		// �^�O�̒ǉ�
		AddTag(L"Player");
		m_currentArmorPoint = m_defaultArmorPoint;
		m_currentHoverTime = m_hoverTime;
		m_bombCount = m_defaultBombCount;
		m_initialPosition = GetTransform()->GetPosition();

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

		// �e�X�g�p�̏����i�_���[�W���󂯂���Ԃ��Ȃ�j
		if (m_isDuringReturn) {
			GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else {
			GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// ���͂̍X�V
		InputUpdate();
		// �ړ�����
		Move();
		// �e�X�g�R�[�h
		TestFanc();
		// ���e�̃����[�h
		BombReload();
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
	}

	void PlayerBase::Jump() {
		GetComponent<Gravity>()->StartJump(m_jumpVerocity);
	}

	void PlayerBase::Hover() {
		// �z�o�[�\���Ԃ�0�ȏ�̏ꍇ�̓z�o�[
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
		// �\������Start��End��2�_�̏�񂪕K�v
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);

		// �e�̔���
		if (bulletAim != Vec3(0.0f) && m_bulletTimer.Count()) {
			m_bulletTimer.Reset();
			GetStage()->AddGameObject<Bullet>(GetThis<PlayerBase>(), ray);
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
		for (auto position : positions)
		{
			auto direction = position - GetTransform()->GetPosition();
			if (direction.lengthSqr() < closestPosition.lengthSqr())
				closestPosition = position;
		}

		auto direction = closestPosition - GetTransform()->GetPosition();
		// y���W�����킹��
		direction.y = launchDirection.y;
		return direction.normalize();
	}

	bool PlayerBase::InViewRange(const Vec3& aimDirection, const Vec3& position)
	{
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
		GetStage()->AddGameObject<Bomb>(GetThis<PlayerBase>(),
			m_predictionLine, GetTransform()->GetPosition(), m_bombPoint);
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

	void PlayerBase::KnockBack(const KnockBackData& data) {
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
		GetComponent<PhysicalBehavior>()->Impact(
			data.Direction, data.Amount * knockBackCorrection);
	}

	void PlayerBase::Respawn() {
		// ���A���Ɏ��񂾏ꍇ���Q�҂ɓ|�����ʒm���s��
		if (m_isDuringReturn) {
			m_aggriever->KilledPlayer();
		}
		m_isDuringReturn = false;
		GetTransform()->SetPosition(m_initialPosition);
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// �A�[�}�[��0�ɂ���
		if (keyState.m_bPressedKeyTbl['0']) {
			m_currentArmorPoint = 0.0f;
			m_isRestoreArmor = true;
			Debug::GetInstance()->Log(L"Test:Armor0");
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
			// ���݂͑J�ڂ��Ȃ��悤�ɂ���
			//Obj->m_weaponStateMachine->ChangeState(PlayerSpecialSkillModeState::Instance());
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
	void PlayerBase::PlayerBombModeState::Enter(const shared_ptr<PlayerBase>& Obj) {}
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
	}
#pragma endregion

	// �K�E�Z�������
#pragma region PlayerSpecialSkillModeState
	shared_ptr<PlayerBase::PlayerSpecialSkillModeState> PlayerBase::PlayerSpecialSkillModeState::Instance() {
		static shared_ptr<PlayerSpecialSkillModeState> instance(new PlayerSpecialSkillModeState);
		return instance;
	}
	void PlayerBase::PlayerSpecialSkillModeState::Enter(const shared_ptr<PlayerBase>& Obj) {
		// �����_�ł͈�񂾂�
		Obj->SpecialSkill();
	}
	void PlayerBase::PlayerSpecialSkillModeState::Execute(const shared_ptr<PlayerBase>& Obj) {
	}
	void PlayerBase::PlayerSpecialSkillModeState::Exit(const shared_ptr<PlayerBase>& Obj) {
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
			if (!Obj->m_isInput)
				Obj->Hover();
		}
		else {
			Obj->m_isInput = false;
		}

		// �ڒn�����ꍇ
		if (Obj->m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// �W�����v�X�e�[�g�֑J��
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion
}