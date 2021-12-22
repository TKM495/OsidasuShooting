/*!
@file   PlayerBase.h
@brief  ƒvƒŒƒCƒ„[
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"
#include "Manager/PlayerManager.h"
#include "Manager/StageManager.h"
#include "StageObject/PlayerModel.h"
#include "Utility/GroundingDecision.h"
#include "Utility/PredictionLine.h"
#include "Utility/TimeCounter.h"
#include "Component/PhysicalBehavior.h"

namespace basecross {
	/**
	 * @brief ƒvƒŒƒCƒ„[‚Ì“ü—Íƒf[ƒ^
	 */
	struct PlayerInputData {
		// ˆÚ“®•ûŒü
		Vec3 MoveDirection;
		// ’e‚ÌŒ‚‚Â•ûŒü
		Vec3 BulletAim;
		// ”š’eƒ‚[ƒh‚ÌÆ€‘€ì
		Vec3 BombAim;
		// Œ‚‚Â‚©‚Ç‚¤‚©
		bool IsFire;

		// ”š’eƒ‚[ƒh‚Ö‚ÌØ‚è‘Ö‚¦i”š’e‚Ì”­Ë‚àŒ“‚Ë‚éj
		bool IsSwitchBombMode;
		// ƒWƒƒƒ“ƒvorƒzƒo[
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
	 * @brief ƒmƒbƒNƒoƒbƒNƒf[ƒ^
	 */
	struct KnockBackData {
		/**
		 * @brief ƒmƒbƒNƒoƒbƒN‚Ìƒ^ƒCƒv
		 */
		enum class Category {
			Bullet, // ’e
			Bomb    // ”š’e
		};

		// ƒ^ƒCƒv
		Category Type;
		// ƒmƒbƒNƒoƒbƒN•ûŒü
		Vec3 Direction;
		// ƒmƒbƒNƒoƒbƒN—Ê
		float Amount;
		// ‰ÁŠQÒ
		weak_ptr<PlayerBase> Aggriever;

		// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
		KnockBackData(
			Category type,
			const Vec3& direction,
			float amount,
			const weak_ptr<PlayerBase>& aggriever)
		{
			this->Type = type;
			this->Direction = direction;
			this->Amount = amount;
			this->Aggriever = aggriever;
		}
	};
	class PlayerBase : public AdvancedGameObject {
	private:
		// ‰ŠúˆÊ’u
		Vec3 m_initialPosition;
		// •Ší—pƒXƒe[ƒgƒ}ƒV[ƒ“
		unique_ptr<StateMachine<PlayerBase>> m_weaponStateMachine;
		// ƒWƒƒƒ“ƒv‚Æƒzƒo[—p‚ÌƒXƒe[ƒgƒ}ƒVƒ“
		unique_ptr<StateMachine<PlayerBase>> m_jumpAndHoverStateMachine;
		// —\‘ªü•\¦ƒNƒ‰ƒX
		PredictionLine m_predictionLine;
		// ”š’e‚Ì’…’eƒ|ƒCƒ“ƒg
		Vec3 m_bombPoint;
		// Œ»İ‚ÌƒGƒlƒ‹ƒM[’l
		float m_currentEnergy;
		// ’e—p‚Ìƒ^ƒCƒ}[
		TimeCounter m_bulletTimer;
		// ”š’e‚ÌƒŠƒ[ƒhƒ^ƒCƒ}[
		TimeCounter m_bombCoolTimeTimer;
		// ”š’e‚ÌŒÂ”
		int m_bombCount;
		// ƒWƒƒƒ“ƒv•ƒzƒo[ƒXƒe[ƒg—p‚Ì˜A‘±‰Ÿ‚µŒŸo—pƒtƒ‰ƒO
		// (State‚ÍƒVƒ“ƒOƒ‹ƒgƒ“‚Å‚ ‚èó‘Ô‚ª‹¤—L‚³‚ê‚Ä‚µ‚Ü‚¤‚½‚ß)
		bool m_isInput;
		// ƒvƒŒƒCƒ„[ƒiƒ“ƒo[
		PlayerNumber m_playerNumber;

		// ‰ÁŠQÒi©•ª‚ÉUŒ‚‚ğ“–‚Ä‚½ƒvƒŒƒCƒ„[j
		weak_ptr<PlayerBase> m_aggriever;
		// •œ‹A’†‚©
		bool m_isDuringReturn;
		// •œ‹A‚µ‚½”»’è‚ğ­‚µ’x‚ç‚¹‚é‚½‚ß‚Ìƒ^ƒCƒ}[
		TimeCounter m_returnTimer;
		// Ú’n”»’è—p
		GroundingDecision m_groundingDecision;
		// ©•ª‚ªƒvƒŒƒCƒ„[‚ğ“|‚µ‚½”
		int m_countKilledPlayer;
		// €‚ñ‚¾‰ñ”
		int m_deadCount;
		// ƒvƒŒƒCƒ„[‚Ìƒ‚ƒfƒ‹
		weak_ptr<PlayerModel> m_model;

		// ‘O‰ñ‚Ì³–Ê•ûŒü
		Vec3 m_lastFrontDirection;

		// ”š’eƒ‚[ƒh‚©
		bool m_isBombMode;
		// ƒzƒo[ƒ‚[ƒh‚©
		bool m_isHoverMode;
		// ˆÚ“®ƒGƒtƒFƒNƒg‚Ìƒ^ƒCƒ}[
		TimeCounter m_smokeTimer;
		// –³“Gƒ^ƒCƒ}[
		TimeCounter m_invincibleTimer;

		//F
		Col4 m_color;
		// –³“G‚©
		bool m_isInvincible;

		// ©g‚ÌƒvƒŒƒCƒ„[ƒ^ƒCƒv
		PlayerType m_playerType;

		// ’e‚ÌˆĞ—Í
		float m_bulletPower;
		// ”š’e‚ÌˆĞ—Í
		float m_bombPower;
		// ’e‚Ì”­Ë‚É•K—v‚ÈƒGƒlƒ‹ƒM[i1”­‚ ‚½‚èj
		float m_energyRequiredInBulletLaunch;
		// ƒzƒo[‚É•K—v‚ÈƒGƒlƒ‹ƒM[i1•b‚ ‚½‚èj
		float m_energyRequiredInHover;

		// ˆÚ“®
		void Move();
		// ’e‚ÌÆ€”­Ë
		Vec3 BulletAim();
		// ’e‚Ì”­Ë
		void BulletLaunch(const Vec3& bulletAim);
		// ’e‚ÌÆ€•â³
		Vec3 BulletAimCorrection(const Vec3& launchDirection);
		/**
		 * @brief ‹–ì”ÍˆÍ“à‚Éposition‚ª‚ ‚é‚©‚Ç‚¤‚©
		 *
		 * @param direction Æ€•ûŒü
		 * @param position ˆÊ’u
		 * @return true‚È‚ç‘¶İ‚·‚é
		 */
		bool InViewRange(const Vec3& aimDirection, const Vec3& position);
		// ”š’e‚ÌÆ€
		void BombAim();
		// ƒWƒƒƒ“ƒv
		void Jump();
		// ƒzƒo[
		void Hover();
		// ƒGƒlƒ‹ƒM[‚Ì‰ñ•œ
		void EnergyRecovery();
		// ”š’e‚Ì”­Ë
		void BombLaunch();
		//// •KE‹Z‚Ì”­“®
		// void SpecialSkill();
		//  “Á’è‚Ì•ûŒü‚É³–Ê‚ğŒü‚¯‚é
		Vec3 TurnFrontToDirection(const Vec3& direction);
		// ƒzƒo[’â~‚Ìˆ—
		void StopHover();
		// –³“Gˆ—
		void Invincible();
		// ƒXƒe[ƒ^ƒX‚Ìƒ[ƒh
		void StatusLoad();
		/**
		 * @brief ƒGƒlƒ‹ƒM[‚ğŒ¸‚ç‚·ic—Ê < Œ¸‚ç‚·—Ê‚Ìê‡‰½‚à‚µ‚È‚¢j
		 *
		 * @param amount Œ¸‚ç‚·—Ê
		 * @return Œ¸‚ç‚¹‚é‚©‚Ç‚¤‚©
		 */
		bool DecrementEnergy(float amount);
		// ƒpƒ‰ƒ[ƒ^‚ÌƒŠƒZƒbƒg
		void ParameterReset();
		/**
		 * @brief ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ñ‚ÌƒGï¿½tï¿½Fï¿½Nï¿½gï¿½`ï¿½ï¿½
		 */
		void KnockBackEffectDrawing();
	protected:
		// ˆÚ“®‘¬“xi‚Ç‚¿‚ç‚©‚Æ‚¢‚¤‚Æ‚©‚¯‚é—Íj
		float m_moveSpeed;
		// ƒWƒƒƒ“ƒv‘¬“x
		Vec3 m_jumpVerocity;
		// ƒfƒtƒHƒ‹ƒg‚ÌƒGƒlƒ‹ƒM[’l
		float m_defaultEnergy;
		// ƒfƒtƒHƒ‹ƒg‚Ì”š’e‚ÌŠ”
		int m_defaultBombCount;
		// ƒA[ƒ}[‚ª0‚Ì‚ÌƒmƒbƒNƒoƒbƒN”{—¦
		float m_armorZeroWhenKnockBackMagnification;
		// ƒGƒlƒ‹ƒM[‚Ì‰ñ•œ‘¬“x
		float m_energyRecoveryAmount;
		// ”š’e‚ÌÆ€‚ÌˆÚ“®‘¬“x
		float m_bombAimMovingDistance;
		// •â³‚·‚éŠp“xi’e‚ÌÆ€j
		float m_correctAngle;
		// “ü—Íƒf[ƒ^
		PlayerInputData m_inputData;
		// “ü—Í‚ÌXV
		virtual void InputUpdate() = 0;
		// ƒŠƒXƒ|[ƒ“‚Ì’Ç‰Áˆ—
		virtual void OnRespawn() {}
		virtual void OnStopHover() {}

	public:
		PlayerBase(const shared_ptr<Stage>& stage,
			const TransformData& transData,
			PlayerNumber playerNumber,
			PlayerType playerType);
		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		// ƒmƒbƒNƒoƒbƒN
		void KnockBack(const KnockBackData& data);
		//ƒŠƒXƒ|[ƒ“
		void Respawn();

		// ƒeƒXƒgŠÖ”
		void TestFanc();

		/**
		 * @brief ƒvƒŒƒCƒ„[‚Ì”Ô†‚ğæ“¾‚·‚é
		 *
		 * @return ƒvƒŒƒCƒ„[ƒiƒ“ƒo[
		 */
		PlayerNumber GetPlayerNumber() {
			return m_playerNumber;
		}

		/**
		 * @brief ƒvƒŒƒCƒ„[‚Ìƒ^ƒCƒv‚ğæ“¾
		 *
		 * @return ƒvƒŒƒCƒ„[ƒ^ƒCƒv
		 */
		PlayerType GetPlayerType() {
			return m_playerType;
		}

		/**
		 * @brief Energy‚Ì(Œ»İ’l / Å‘å’l)‚ğæ“¾‚·‚é
		 *
		 * @return (Œ»İ’l / Å‘å’l)
		 */
		float GetEnergyRate() {
			return m_currentEnergy / m_defaultEnergy;
		}

		/**
		 * @brief ”š’e‚Ìc’e”‚ğæ“¾‚·‚é
		 *
		 * @return ”š’e‚Ìc’e”
		 */
		int GetBombCount() {
			return m_bombCount;
		}

		/**
		 * @brief ”š’e‚ÌƒN[ƒ‹ƒ^ƒCƒ€‚ÌŠ„‡‚ğæ“¾
		 *
		 * @return ƒN[ƒ‹ƒ^ƒCƒ€‚ÌŠ„‡
		 */
		float GetBombCoolTimeRate() {
			return m_bombCoolTimeTimer.GetTimeRate();
		}

		/**
		 * @brief ƒvƒŒƒCƒ„[‚ğ“|‚µ‚½
		 */
		void KilledPlayer() {
			m_countKilledPlayer++;
		}

		/**
		 * @brief ƒvƒŒƒCƒ„[‚ğ“|‚µ‚½”‚ğæ“¾
		 *
		 * @return ƒvƒŒƒCƒ„[‚ğ“|‚µ‚½”
		 */
		int GetCountKilledPlayer() {
			return m_countKilledPlayer;
		}

		/**
		 * @brief €‚ñ‚¾‰ñ”‚ğæ“¾
		 *
		 * @return €‚ñ‚¾‰ñ”
		 */
		int GetDeadCount() {
			return m_deadCount;
		}

		/**
		 * @brief F‚ğæ“¾
		 *
		 * @return F
		 */
		Col4 GetColor() {
			return m_color;
		}

		/**
		 * @brief ”š’eƒ‚[ƒh‚©
		 *
		 * @return true‚È‚ç‚»‚¤
		 */
		bool IsBombMode() {
			return m_isBombMode;
		}
		/**
		 * @brief ƒzƒo[ƒ‚[ƒh‚©
		 *
		 * @return true‚È‚ç‚»‚¤
		 */
		bool IsHoverMode() {
			return m_isHoverMode;
		}

		/**
		 * @brief –³“G‚©
		 *
		 * @return true‚È‚ç‚»‚¤
		 */
		bool IsInvincible() {
			return m_isInvincible;
		}

		/**
		 * @brief ³–Ê•ûŒü‚Ìæ“¾
		 *
		 * @return ³–Ê•ûŒü‚ÌƒxƒNƒgƒ‹
		 */
		Vec3 GetDirectionToFace() {
			return m_lastFrontDirection;
		}

		/**
		 * @brief Œ»İ‚Ì‘¬“x‚ğæ“¾
		 *
		 * @return Œ»İ‚Ì‘¬“x
		 */
		Vec3 GetVelocity() {
			return GetComponent<PhysicalBehavior>()->GetVelocity();
		}

	private:
		// •Ší—pƒXƒe[ƒg
#pragma region WeaponState
		// ’e‚ÌÆ€‚â”­Ëó‘ÔiƒfƒtƒHƒ‹ƒgj
		class PlayerBulletModeState : public ObjState<PlayerBase> {
			PlayerBulletModeState() {}

		public:
			static shared_ptr<PlayerBulletModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};

		// ”š’e‚ÌÆ€‚â”­Ëó‘Ô
		class PlayerBombModeState : public ObjState<PlayerBase> {
			PlayerBombModeState() {}

		public:
			static shared_ptr<PlayerBombModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
#pragma endregion

		// ƒWƒƒƒ“ƒv‚Æƒzƒo[—p‚ÌƒXƒe[ƒg
#pragma region JumpAndHoverState
		// ƒWƒƒƒ“ƒviƒfƒtƒHƒ‹ƒgj
		class PlayerJumpState : public ObjState<PlayerBase> {
			PlayerJumpState() {}

		public:
			static shared_ptr<PlayerJumpState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
		// ƒzƒo[
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
