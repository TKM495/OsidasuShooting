/*!
@file   PlayerBase.h
@brief  �v���C���[
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "Utility/PredictionLine.h"

namespace basecross {
	/**
	 * @brief �v���C���[�̓��̓f�[�^
	 */
	struct PlayerInputData {
		// �ړ�����
		Vec3 MoveDirection;
		// �e�̌�����
		Vec3 BulletAim;
		// ���e���[�h���̏Ə�����
		Vec3 BombAim;

		// ���e���[�h�ւ̐؂�ւ��i���e�̔��˂����˂�j
		bool IsSwitchBombMode;
		// �K�E�Z����
		bool IsInvokeSpecialSkill;
		// �W�����vor�z�o�[
		bool IsJumpOrHover;
	};

	class PlayerBase :public StageObject {
	private:
		// ����p�X�e�[�g�}�V�[��
		unique_ptr<StateMachine<PlayerBase>> m_weaponStateMachine;
		// �W�����v�ƃz�o�[�p�̃X�e�[�g�}�V��
		unique_ptr<StateMachine<PlayerBase>> m_jumpAndHoverStateMachine;
		// �\�����\���N���X
		PredictionLine m_predictionLine;
		// ���e�̒��e�|�C���g
		Vec3 m_bombPoint;
		// ���݂̃z�o�[�\����
		float m_currentHoverTime;
		// ���݂̃A�[�}�[�l
		float m_currentArmorPoint;

		// �ړ�
		void Move();
		// �e�̏Ə��Ɣ���
		void BulletAimAndLaunch();
		// ���e�̏Ə�
		void BombAim();
		// �W�����v
		void Jump();
		// �z�o�[
		void Hover();
		// �z�o�[�\���ԉ�
		void HoverTimeRecovery();
		// ���e�̔���
		void BombLaunch();
		// �K�E�Z�̔���
		void SpecialSkill();
	protected:
		// �ړ����x�i�ǂ��炩�Ƃ����Ƃ�����́j
		float m_moveSpeed;
		// �W�����v���x
		Vec3 m_jumpVerocity;
		// �z�o�[�\����
		float m_hoverTime;
		// �f�t�H���g�̃A�[�}�[�l
		float m_defaultArmorPoint;
		// ���̓f�[�^
		PlayerInputData m_inputData;
		// ���͂̍X�V
		virtual void InputUpdate() = 0;

	public:
		PlayerBase(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage), m_moveSpeed(20.0f), m_predictionLine(stage, 10, 2.0f),
			m_bombPoint(Vec3(0.0f)), m_jumpVerocity(Vec3(0.0f, 10.0f, 0.0f)),
			m_hoverTime(5.0f), m_currentHoverTime(m_hoverTime),
			m_defaultArmorPoint(100.0f), m_currentArmorPoint(m_defaultArmorPoint)
		{
			m_transformData = transData;
		}
		void OnCreate()override;
		void OnUpdate()override;

		// �m�b�N�o�b�N
		void KnockBack(const Vec3& knockBackDirection, float knockBackAmount);
		//���X�|�[��
		void Respawn();
	private:
		// ����p�X�e�[�g
#pragma region WeaponState
	// �e�̏Ə��┭�ˏ�ԁi�f�t�H���g�j
		class PlayerBulletModeState : public ObjState<PlayerBase> {
			PlayerBulletModeState() {}
		public:
			static shared_ptr<PlayerBulletModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};

		// ���e�̏Ə��┭�ˏ��
		class PlayerBombModeState : public ObjState<PlayerBase> {
			PlayerBombModeState() {}
		public:
			static shared_ptr<PlayerBombModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};

		// �K�E�Z�������
		class PlayerSpecialSkillModeState : public ObjState<PlayerBase> {
			PlayerSpecialSkillModeState() {}
		public:
			static shared_ptr<PlayerSpecialSkillModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
#pragma endregion

		// �W�����v�ƃz�o�[�p�̃X�e�[�g
#pragma region JumpAndHoverState
	// �W�����v�i�f�t�H���g�j
		class PlayerJumpState : public ObjState<PlayerBase> {
			// �J�ڑO���牟����Ă��邩�̃t���O
			bool m_isPushed;
			PlayerJumpState()
				:m_isPushed(false)
			{}
		public:
			static shared_ptr<PlayerJumpState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
		// �z�o�[
		class PlayerHoverState : public ObjState<PlayerBase> {
			// �J�ڑO���牟����Ă��邩�̃t���O
			bool m_isPushed;
			GroundingDecision m_groundingDecision;
			PlayerHoverState()
				:m_isPushed(false), m_groundingDecision()
			{}
		public:
			static shared_ptr<PlayerHoverState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
#pragma endregion
	};
}
