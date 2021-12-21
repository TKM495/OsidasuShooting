/*!
@file   PlayerBase.h
@brief  �v���C���[
*/

#pragma once
#include "AdvancedGameObject.h"
#include "Manager/PlayerManager.h"
#include "Manager/StageManager.h"
#include "StageObject/PlayerModel.h"
#include "Utility/GroundingDecision.h"
#include "Utility/PredictionLine.h"
#include "Utility/TimeCounter.h"
#include "stdafx.h"

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
		// �����ǂ���
		bool IsFire;

		// ���e���[�h�ւ̐؂�ւ��i���e�̔��˂����˂�j
		bool IsSwitchBombMode;
		// �W�����vor�z�o�[
		bool IsJumpOrHover;

		PlayerInputData() {
			this->MoveDirection = Vec3(0.0f);
			this->BulletAim = Vec3(0.0f);
			this->BombAim = Vec3(0.0f);
			this->IsFire = false;
			this->IsSwitchBombMode = false;
			this->IsJumpOrHover = false;
		}
	};

	/**
	 * @brief �m�b�N�o�b�N�f�[�^
	 */
	struct KnockBackData {
		/**
		 * @brief �m�b�N�o�b�N�̃^�C�v
		 */
		enum class Category {
			Bullet, // �e
			Bomb    // ���e
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
			const weak_ptr<PlayerBase>& aggriever) {
			this->Type = type;
			this->Direction = direction;
			this->Amount = amount;
			this->Aggriever = aggriever;
		}
	};
	class PlayerBase : public AdvancedGameObject {
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
		// ���݂̃G�l���M�[�l
		float m_currentEnergy;
		// �e�p�̃^�C�}�[
		TimeCounter m_bulletTimer;
		// ���e�̃����[�h�^�C�}�[
		TimeCounter m_bombCoolTimeTimer;
		// ���e�̌�
		int m_bombCount;
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
		// ���񂾉�
		int m_deadCount;
		// �v���C���[�̃��f��
		weak_ptr<PlayerModel> m_model;

		// �O��̐��ʕ���
		Vec3 m_lastFrontDirection;

		// ���e���[�h��
		bool m_isBombMode;
		// �z�o�[���[�h��
		bool m_isHoverMode;
		// �ړ��G�t�F�N�g�̃^�C�}�[
		TimeCounter m_smokeTimer;
		// ���G�^�C�}�[
		TimeCounter m_invincibleTimer;

		//�F
		Col4 m_color;
		// ���G��
		bool m_isInvincible;

		// ���g�̃v���C���[�^�C�v
		PlayerType m_playerType;

		// �e�̈З�
		float m_bulletPower;
		// ���e�̈З�
		float m_bombPower;
		// �e�̔��˂ɕK�v�ȃG�l���M�[�i1��������j
		float m_energyRequiredInBulletLaunch;
		// �z�o�[�ɕK�v�ȃG�l���M�[�i1�b������j
		float m_energyRequiredInHover;

		// �ړ�
		void Move();
		// �e�̏Ə�����
		Vec3 BulletAim();
		// �e�̔���
		void BulletLaunch(const Vec3& bulletAim);
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
		// �W�����v
		void Jump();
		// �z�o�[
		void Hover();
		// �G�l���M�[�̉�
		void EnergyRecovery();
		// ���e�̔���
		void BombLaunch();
		//// �K�E�Z�̔���
		// void SpecialSkill();
		//  ����̕����ɐ��ʂ�������
		Vec3 TurnFrontToDirection(const Vec3& direction);
		// �z�o�[��~���̏���
		void StopHover();
		// ���G����
		void Invincible();
		// �X�e�[�^�X�̃��[�h
		void StatusLoad();
		/**
		 * @brief �G�l���M�[�����炷�i�c�� < ���炷�ʂ̏ꍇ�������Ȃ��j
		 *
		 * @param amount ���炷��
		 * @return ���点�邩�ǂ���
		 */
		bool DecrementEnergy(float amount);
		// �p�����[�^�̃��Z�b�g
		void ParameterReset();

	protected:
		// �ړ����x�i�ǂ��炩�Ƃ����Ƃ�����́j
		float m_moveSpeed;
		// �W�����v���x
		Vec3 m_jumpVerocity;
		// �f�t�H���g�̃G�l���M�[�l
		float m_defaultEnergy;
		// �f�t�H���g�̔��e�̏�����
		int m_defaultBombCount;
		// �A�[�}�[��0�̎��̃m�b�N�o�b�N�{��
		float m_armorZeroWhenKnockBackMagnification;
		// �G�l���M�[�̉񕜑��x
		float m_energyRecoveryAmount;
		// ���e�̏Ə��̈ړ����x
		float m_bombAimMovingDistance;
		// �␳����p�x�i�e�̏Ə��j
		float m_correctAngle;
		// ���̓f�[�^
		PlayerInputData m_inputData;
		// ���͂̍X�V
		virtual void InputUpdate() = 0;
		// ���X�|�[�����̒ǉ�����
		virtual void OnRespawn() {}
		virtual void OnStopHover() {}

	public:
		PlayerBase(const shared_ptr<Stage>& stage,
			const TransformData& transData,
			PlayerNumber playerNumber,
			PlayerType playerType);
		void OnCreate() override;
		void OnUpdate() override;

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
		 * @brief �v���C���[�̃^�C�v���擾
		 *
		 * @return �v���C���[�^�C�v
		 */
		PlayerType GetPlayerType() {
			return m_playerType;
		}

		/**
		 * @brief Energy��(���ݒl / �ő�l)���擾����
		 *
		 * @return (���ݒl / �ő�l)
		 */
		float GetEnergyRate() {
			return m_currentEnergy / m_defaultEnergy;
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
		 * @brief ���e�̃N�[���^�C���̊������擾
		 *
		 * @return �N�[���^�C���̊���
		 */
		float GetBombCoolTimeRate() {
			return m_bombCoolTimeTimer.GetTimeRate();
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

		/**
		 * @brief ���񂾉񐔂��擾
		 *
		 * @return ���񂾉�
		 */
		int GetDeadCount() {
			return m_deadCount;
		}

		/**
		 * @brief �F���擾
		 *
		 * @return �F
		 */
		Col4 GetColor() {
			return m_color;
		}

		/**
		 * @brief ���e���[�h��
		 *
		 * @return true�Ȃ炻��
		 */
		bool IsBombMode() {
			return m_isBombMode;
		}
		/**
		 * @brief �z�o�[���[�h��
		 *
		 * @return true�Ȃ炻��
		 */
		bool IsHoverMode() {
			return m_isHoverMode;
		}

		/**
		 * @brief ���G��
		 *
		 * @return true�Ȃ炻��
		 */
		bool IsInvincible() {
			return m_isInvincible;
		}

		/**
		 * @brief ���ʕ����̎擾
		 *
		 * @return ���ʕ����̃x�N�g��
		 */
		Vec3 GetDirectionToFace() {
			return m_lastFrontDirection;
		}

	private:
		// ����p�X�e�[�g
#pragma region WeaponState
		// �e�̏Ə��┭�ˏ�ԁi�f�t�H���g�j
		class PlayerBulletModeState : public ObjState<PlayerBase> {
			PlayerBulletModeState() {}

		public:
			static shared_ptr<PlayerBulletModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};

		// ���e�̏Ə��┭�ˏ��
		class PlayerBombModeState : public ObjState<PlayerBase> {
			PlayerBombModeState() {}

		public:
			static shared_ptr<PlayerBombModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
#pragma endregion

		// �W�����v�ƃz�o�[�p�̃X�e�[�g
#pragma region JumpAndHoverState
		// �W�����v�i�f�t�H���g�j
		class PlayerJumpState : public ObjState<PlayerBase> {
			PlayerJumpState() {}

		public:
			static shared_ptr<PlayerJumpState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
		// �z�o�[
		class PlayerHoverState : public ObjState<PlayerBase> {
			PlayerHoverState() {}

		public:
			static shared_ptr<PlayerHoverState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
#pragma endregion
	};
}
