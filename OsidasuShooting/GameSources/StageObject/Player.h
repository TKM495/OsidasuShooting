/*!
@file   Player.h
@brief  プレイヤー
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
		// 移動速度（どちらかというとかける力）
		float m_moveSpeed;
		// 予測線表示クラス
		PredictionLine m_predictionLine;
		// 爆弾の着弾ポイント
		Vec3 m_bombPoint;
		// ジャンプ速度
		Vec3 m_jumpVerocity;
		// 武器用ステートマシーン
		unique_ptr<StateMachine<Player>> m_weaponStateMachine;
		// ジャンプとホバー用のステートマシン
		unique_ptr<StateMachine<Player>> m_jumpAndHoverStateMachine;
		// ホバー可能時間
		float m_hoverTime;
		// 現在のホバー可能時間
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

		// ジャンプ
		void Jump();
		// ホバー
		void Hover();
		//
		void HoverTimeRecovery();

		void BulletAimAndLaunch();
		void BombAim();
		void BombLaunch();
		void SpecialSkill();
	};

	// 武器用ステート
#pragma region WeaponState
	// 弾の照準や発射状態（デフォルト）
	class PlayerBulletModeState : public ObjState<Player> {
		PlayerBulletModeState() {}
	public:
		static shared_ptr<PlayerBulletModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	// 爆弾の照準や発射状態
	class PlayerBombModeState : public ObjState<Player> {
		PlayerBombModeState() {}
	public:
		static shared_ptr<PlayerBombModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	// 必殺技発動状態
	class PlayerSpecialSkillModeState : public ObjState<Player> {
		PlayerSpecialSkillModeState() {}
	public:
		static shared_ptr<PlayerSpecialSkillModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
#pragma endregion

	// ジャンプとホバー用のステート
#pragma region JumpAndHoverState
	// 移動（デフォルト）（移動自体は）
	class PlayerMoveState : public ObjState<Player> {
		PlayerMoveState() {}
	public:
		static shared_ptr<PlayerMoveState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	// ジャンプ
	class PlayerJumpState : public ObjState<Player> {
		// 遷移前から押されているかのフラグ
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
	// ホバー
	class PlayerHoverState : public ObjState<Player> {
		// 遷移前から押されているかのフラグ
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
