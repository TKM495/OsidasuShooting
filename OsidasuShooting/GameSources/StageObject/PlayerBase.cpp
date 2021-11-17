/*!
@file   PlayerBase.cpp
@brief  �v���C���[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerBase::OnCreate() {
		// �V�F�A�I�u�W�F�N�g�ɓo�^�i�ŏI�I�ɕ����ɂȂ�̂ŗv�����j
		//GetStage()->SetSharedGameObject(L"PlayerBase", GetThis<PlayerBase>());

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
	}

	void PlayerBase::OnUpdate() {
		// ���͂̍X�V
		InputUpdate();
		// �ړ�����
		Move();
		// �e�X�g�R�[�h
		TestFanc();
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
		GetStage()->AddGameObject<SpecialCamera>();
	}

	void PlayerBase::BulletAimAndLaunch() {
		auto userPosition = GetTransform()->GetPosition();
		Ray ray(userPosition, m_inputData.BulletAim.normalize());
		// �\������Start��End��2�_�̏�񂪕K�v
		m_predictionLine.Update(ray.Origin, ray.GetPoint(3.0f), PredictionLine::Type::Bullet);

		// �e�̔���
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

	void PlayerBase::BombReload() {
		// ���̎��Ԃ��o�߂�����
		if (m_bombReload.Count()) {
			// ���݂̔��e�̐����ő吔�ȏ�̏ꍇ�͉������Ȃ�
			if (m_bombCount < m_defaultBombCount) {
				// �ő吔�ȏ�ł͂Ȃ��Ƃ��c�e�𑝂₵�A�^�C�}�[�����Z�b�g
				m_bombCount++;
				m_bombReload.Reset();
			}
		}
	}

	void PlayerBase::BombLaunch() {
		GetStage()->AddGameObject<Bomb>(
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

	void PlayerBase::KnockBack(const Vec3& knockBackDirection, float knockBackAmount) {
		float knockBackCorrection;
		// �A�[�}�[���񕜒��łȂ��@���@�A�[�}�[��0���傫��
		if (m_currentArmorPoint > 0 && !m_isRestoreArmor)
		{
			knockBackCorrection = 1;
			m_currentArmorPoint -= 5;
		}
		else
		{
			knockBackCorrection = 5.0f;
			m_isRestoreArmor = true;
		}
		GetComponent<PhysicalBehavior>()->Impact(
			knockBackDirection, knockBackAmount * knockBackCorrection);
	}

	void PlayerBase::Respawn() {
		GetTransform()->SetPosition(m_initialPosition);
	}

	void PlayerBase::TestFanc() {
		const auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		// �A�[�}�[��0�ɂ���
		if (keyState.m_bPressedKeyTbl['0']) {
			m_currentArmorPoint = 0.0f;
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
		if (Obj->m_inputData.IsInvokeSpecialSkill)
			Obj->m_weaponStateMachine->ChangeState(PlayerSpecialSkillModeState::Instance());
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
		// �ڒn����̏���������
		m_groundingDecision.SetRadius(Obj->GetTransform()->GetScale());
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
		if (m_groundingDecision.Calculate(Obj->GetTransform()->GetPosition()))
			// �W�����v�X�e�[�g�֑J��
			Obj->m_jumpAndHoverStateMachine->ChangeState(PlayerJumpState::Instance());
	}
	void PlayerBase::PlayerHoverState::Exit(const shared_ptr<PlayerBase>& Obj) {}
#pragma endregion
}