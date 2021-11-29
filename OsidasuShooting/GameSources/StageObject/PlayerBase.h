/*!
@file   PlayerBase.h
@brief  �v���C���[
*/

#pragma once
#include "stdafx.h"
#include "Manager/PlayerManager.h"
#include "AdvancedGameObject.h"
#include "Utility/PredictionLine.h"
#include "Utility/TimeCounter.h"
#include "Utility/GroundingDecision.h"

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

		PlayerInputData() {
			this->MoveDirection = Vec3(0.0f);
			this->BulletAim = Vec3(0.0f);
			this->BombAim = Vec3(0.0f);
			this->IsSwitchBombMode = false;
			this->IsInvokeSpecialSkill = false;
			this->IsJumpOrHover = false;
		}
	};

	class PlayerBase :public AdvancedGameObject {
	public:
		/**
		 * @brief �m�b�N�o�b�N�f�[�^
		 */
		struct KnockBackData {
			/**
			 * @brief �m�b�N�o�b�N�̃^�C�v
			 */
			enum class Category {
				Bullet,	// �e
				Bomb	// ���e
			};

			// �^�C�v
			Category Type;
			// �m�b�N�o�b�N����
			Vec3 Direction;
			// �m�b�N�o�b�N��
			float Amount;
			// ���Q��
			weak_ptr<PlayerBase> Aggriever;

			// �R���X�g���N�^
			KnockBackData(
				Category type,
				const Vec3& direction,
				float amount,
				const weak_ptr<PlayerBase>& aggriever
			) {
				this->Type = type;
				this->Direction = direction;
				this->Amount = amount;
				this->Aggriever = aggriever;
			}
		};
	private:
		// �����ʒu
		Vec3 m_initialPosition;
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
		// �e�p�̃^�C�}�[
		TimeCounter m_bulletTimer;
		// �A�[�}�[�񕜊J�n�܂ł̎���
		TimeCounter m_armorRecoveryTimer;
		// ���e�̃����[�h�^�C�}�[
		TimeCounter m_bombReload;
		// ���e�̌�
		int m_bombCount;
		// �A�[�}�[���񕜒���
		bool m_isRestoreArmor;
		// �W�����v���z�o�[�X�e�[�g�p�̘A���������o�p�t���O
		// (State�̓V���O���g���ł����Ԃ����L����Ă��܂�����)
		bool m_isInput;
		// �v���C���[�i���o�[
		PlayerNumber m_playerNumber;

		// ���Q�ҁi�����ɍU���𓖂Ă��v���C���[�j
		weak_ptr<PlayerBase> m_aggriever;
		// ���A����
		bool m_isDuringReturn;
		// ���A��������������x�点�邽�߂̃^�C�}�[
		TimeCounter m_returnTimer;
		// �ڒn����p
		GroundingDecision m_groundingDecision;
		// �������v���C���[��|������
		int m_countKilledPlayer;

		// �O��̐��ʕ���
		Vec3 m_lastFrontDirection;

		// �ړ�
		void Move();
		// �e�̏Ə��Ɣ���
		void BulletAimAndLaunch();
		// �e�̏Ə��␳
		Vec3 BulletAimCorrection(const Vec3& launchDirection);
		/**
		 * @brief ����͈͓���position�����邩�ǂ���
		 *
		 * @param direction �Ə�����
		 * @param position �ʒu
		 * @return true�Ȃ瑶�݂���
		 */
		bool InViewRange(const Vec3& aimDirection, const Vec3& position);
		// ���e�̏Ə�
		void BombAim();
		// ���e�̃����[�h
		void BombReload();
		// �W�����v
		void Jump();
		// �z�o�[
		void Hover();
		// �z�o�[�\���ԉ�
		void HoverTimeRecovery();
		// �A�[�}�[�̉�
		void ArmorRecovery();
		// ���e�̔���
		void BombLaunch();
		// �K�E�Z�̔���
		void SpecialSkill();
		// ����̕����ɐ��ʂ�������
		void TurnFrontToDirection(const Vec3& direction);
	protected:
		// �ړ����x�i�ǂ��炩�Ƃ����Ƃ�����́j
		float m_moveSpeed;
		// �W�����v���x
		Vec3 m_jumpVerocity;
		// �z�o�[�\����
		float m_hoverTime;
		// �f�t�H���g�̃A�[�}�[�l
		float m_defaultArmorPoint;
		// �f�t�H���g�̔��e�̏�����
		int m_defaultBombCount;
		// �␳����p�x�i�e�̏Ə��j
		float m_correctAngle;
		// ���̓f�[�^
		PlayerInputData m_inputData;
		// ���͂̍X�V
		virtual void InputUpdate() = 0;

	public:
		PlayerBase(const shared_ptr<Stage>& stage,
			const TransformData& transData,
			PlayerNumber playerNumber)
			:AdvancedGameObject(stage), m_initialPosition(0.0f),
			m_moveSpeed(20.0f), m_predictionLine(stage, 10, 2.0f),
			m_bombPoint(Vec3(0.0f)), m_jumpVerocity(Vec3(0.0f, 10.0f, 0.0f)),
			m_hoverTime(5.0f), m_currentHoverTime(m_hoverTime),
			m_defaultArmorPoint(100.0f), m_currentArmorPoint(m_defaultArmorPoint),
			m_bulletTimer(0.1f, true), m_armorRecoveryTimer(2.0f),
			m_isRestoreArmor(false), m_isInput(false), m_playerNumber(playerNumber),
			m_bombReload(1.0f), m_defaultBombCount(5), m_correctAngle(40.0f),
			m_isDuringReturn(false), m_groundingDecision(), m_countKilledPlayer(0),
			m_returnTimer(0.5f), m_lastFrontDirection(Vec3(0.0f))
		{
			m_transformData = transData;
			m_transformData.Scale *= 2.0f;
			// �ȉ��̃^�O�����I�u�W�F�N�g�𔻒肩�珜�O
			m_groundingDecision.AddNotDecisionTag(L"Bomb");
			m_groundingDecision.AddNotDecisionTag(L"Bullet");
		}
		void OnCreate()override;
		void OnUpdate()override;

		// �m�b�N�o�b�N
		void KnockBack(const KnockBackData& data);
		//���X�|�[��
		void Respawn();
		// �e�X�g�֐�
		void TestFanc();

		/**
		 * @brief �v���C���[�̔ԍ����擾����
		 *
		 * @return �v���C���[�i���o�[
		 */
		PlayerNumber GetPlayerNumber() {
			return m_playerNumber;
		}

		/**
		 * @brief �A�[�}�[��(���ݒl / �ő�l)���擾����
		 *
		 * @return (���ݒl / �ő�l)
		 */
		float GetArmorPointRate() {
			return m_currentArmorPoint / m_defaultArmorPoint;
		}

		/**
		 * @brief �z�o�[�\���Ԃ�(���ݒl / �ő�l)���擾����
		 *
		 * @return (���ݒl / �ő�l)
		 */
		float GetHoverTimeRate() {
			return m_currentHoverTime / m_hoverTime;
		}

		/**
		 * @brief ���e�̃����[�h�̎��Ԃ̊������擾����
		 *
		 * @return���e�̃����[�h�̎��Ԃ̊���
		 */
		float GetBombReloadRate() {
			return m_bombReload.GetTimeRate();
		}

		/**
		 * @brief ���e�̎c�e�����擾����
		 *
		 * @return ���e�̎c�e��
		 */
		int GetBombCount() {
			return m_bombCount;
		}

		/**
		 * @brief �v���C���[��|����
		 */
		void KilledPlayer() {
			m_countKilledPlayer++;
		}

		/**
		 * @brief �v���C���[��|���������擾
		 *
		 * @return �v���C���[��|������
		 */
		int GetCountKilledPlayer() {
			return m_countKilledPlayer;
		}

		void SetColor(const Col4& color) {
			GetComponent<PNTStaticDraw>()->SetDiffuse(color);
		}
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
			PlayerJumpState() {}
		public:
			static shared_ptr<PlayerJumpState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
		// �z�o�[
		class PlayerHoverState : public ObjState<PlayerBase> {
			PlayerHoverState() {}
		public:
			static shared_ptr<PlayerHoverState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
#pragma endregion
	};
}
