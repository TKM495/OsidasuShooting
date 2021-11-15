/*!
@file   PlayerBase.h
@brief  プレイヤー
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "Utility/PredictionLine.h"

namespace basecross {
	/**
	 * @brief プレイヤーの入力データ
	 */
	struct PlayerInputData {
		// 移動方向
		Vec3 MoveDirection;
		// 弾の撃つ方向
		Vec3 BulletAim;
		// 爆弾モード時の照準操作
		Vec3 BombAim;

		// 爆弾モードへの切り替え（爆弾の発射も兼ねる）
		bool IsSwitchBombMode;
		// 必殺技発動
		bool IsInvokeSpecialSkill;
		// ジャンプorホバー
		bool IsJumpOrHover;
	};

	class PlayerBase :public StageObject {
	private:
		// 武器用ステートマシーン
		unique_ptr<StateMachine<PlayerBase>> m_weaponStateMachine;
		// ジャンプとホバー用のステートマシン
		unique_ptr<StateMachine<PlayerBase>> m_jumpAndHoverStateMachine;
		// 予測線表示クラス
		PredictionLine m_predictionLine;
		// 爆弾の着弾ポイント
		Vec3 m_bombPoint;
		// 現在のホバー可能時間
		float m_currentHoverTime;
		// 現在のアーマー値
		float m_currentArmorPoint;

		// 移動
		void Move();
		// 弾の照準と発射
		void BulletAimAndLaunch();
		// 爆弾の照準
		void BombAim();
		// ジャンプ
		void Jump();
		// ホバー
		void Hover();
		// ホバー可能時間回復
		void HoverTimeRecovery();
		// 爆弾の発射
		void BombLaunch();
		// 必殺技の発動
		void SpecialSkill();
	protected:
		// 移動速度（どちらかというとかける力）
		float m_moveSpeed;
		// ジャンプ速度
		Vec3 m_jumpVerocity;
		// ホバー可能時間
		float m_hoverTime;
		// デフォルトのアーマー値
		float m_defaultArmorPoint;
		// 入力データ
		PlayerInputData m_inputData;
		// 入力の更新
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

		// ノックバック
		void KnockBack(const Vec3& knockBackDirection, float knockBackAmount);
		//リスポーン
		void Respawn();
	private:
		// 武器用ステート
#pragma region WeaponState
	// 弾の照準や発射状態（デフォルト）
		class PlayerBulletModeState : public ObjState<PlayerBase> {
			PlayerBulletModeState() {}
		public:
			static shared_ptr<PlayerBulletModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};

		// 爆弾の照準や発射状態
		class PlayerBombModeState : public ObjState<PlayerBase> {
			PlayerBombModeState() {}
		public:
			static shared_ptr<PlayerBombModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};

		// 必殺技発動状態
		class PlayerSpecialSkillModeState : public ObjState<PlayerBase> {
			PlayerSpecialSkillModeState() {}
		public:
			static shared_ptr<PlayerSpecialSkillModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
#pragma endregion

		// ジャンプとホバー用のステート
#pragma region JumpAndHoverState
	// ジャンプ（デフォルト）
		class PlayerJumpState : public ObjState<PlayerBase> {
			// 遷移前から押されているかのフラグ
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
		// ホバー
		class PlayerHoverState : public ObjState<PlayerBase> {
			// 遷移前から押されているかのフラグ
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
