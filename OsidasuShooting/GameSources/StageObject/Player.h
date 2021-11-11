/*!
@file   Player.h
@brief  �v���C���[
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "Utility/PredictionLine.h"

namespace basecross {
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	class Player :public StageObject {
		// �ړ����x�i�ǂ��炩�Ƃ����Ƃ�����́j
		float m_moveSpeed;
		// �\�����\���N���X
		PredictionLine m_predictionLine;
		// ���e�̒��e�|�C���g
		Vec3 m_bombPoint;
		// �W�����v���x
		Vec3 m_jumpVerocity;
		// ����p�X�e�[�g�}�V�[��
		unique_ptr<StateMachine<Player>> m_weaponStateMachine;
		// �W�����v�ƃz�o�[�p�̃X�e�[�g�}�V��
		unique_ptr<StateMachine<Player>> m_jumpAndHoverStateMachine;
		// �z�o�[�\����
		float m_hoverTime;
		// ���݂̃z�o�[�\����
		float m_currentHoverTime;

		void Move();
	public:
		Player(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage), m_moveSpeed(20.0f), m_predictionLine(stage, 10, 2.0f),
			m_bombPoint(Vec3(0.0f)), m_jumpVerocity(Vec3(0.0f, 10.0f, 0.0f)),
			m_hoverTime(5.0f), m_currentHoverTime(m_hoverTime)
		{
			m_transformData = transData;
		}
		void OnCreate()override;
		void OnUpdate()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		void OnCollisionExcute(shared_ptr<GameObject>& other)override;
		void OnCollisionExit(shared_ptr<GameObject>& other)override;

		const unique_ptr<StateMachine<Player>>& GetWeaponStateMachine() {
			return m_weaponStateMachine;
		}
		const unique_ptr<StateMachine<Player>>& GetJumpAndHoverStateMachine() {
			return m_jumpAndHoverStateMachine;
		}

		// �W�����v
		void Jump();
		// �z�o�[
		void Hover();
		//
		void HoverTimeRecovery();

		void BulletAimAndLaunch();
		void BombAim();
		void BombLaunch();
		void SpecialSkill();
	};

	// ����p�X�e�[�g
#pragma region WeaponState
	// �e�̏Ə��┭�ˏ�ԁi�f�t�H���g�j
	class PlayerBulletModeState : public ObjState<Player> {
		PlayerBulletModeState() {}
	public:
		static shared_ptr<PlayerBulletModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	// ���e�̏Ə��┭�ˏ��
	class PlayerBombModeState : public ObjState<Player> {
		PlayerBombModeState() {}
	public:
		static shared_ptr<PlayerBombModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	// �K�E�Z�������
	class PlayerSpecialSkillModeState : public ObjState<Player> {
		PlayerSpecialSkillModeState() {}
	public:
		static shared_ptr<PlayerSpecialSkillModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
#pragma endregion

	// �W�����v�ƃz�o�[�p�̃X�e�[�g
#pragma region JumpAndHoverState
	// �ړ��i�f�t�H���g�j�i�ړ����̂́j
	class PlayerMoveState : public ObjState<Player> {
		PlayerMoveState() {}
	public:
		static shared_ptr<PlayerMoveState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	// �W�����v
	class PlayerJumpState : public ObjState<Player> {
		// �J�ڑO���牟����Ă��邩�̃t���O
		bool m_isPushedLeftTrigger;
		PlayerJumpState()
			:m_isPushedLeftTrigger(false)
		{}
	public:
		static shared_ptr<PlayerJumpState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	// �z�o�[
	class PlayerHoverState : public ObjState<Player> {
		// �J�ڑO���牟����Ă��邩�̃t���O
		bool m_isPushedLeftTrigger;
		GroundingDecision m_groundingDecision;
		PlayerHoverState()
			:m_isPushedLeftTrigger(false), m_groundingDecision()
		{}
	public:
		static shared_ptr<PlayerHoverState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
#pragma endregion
}
