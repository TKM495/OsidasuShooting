/*!
@file   Player.h
@brief  プレイヤー
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "Utility/BombPredictionLine.h"

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
		BombPredictionLine line;
		// 爆弾の着弾ポイント
		Vec3 m_bombPoint;
		// ジャンプ速度
		Vec3 m_jumpVerocity;
		//ステートマシーン
		unique_ptr<StateMachine<Player>> m_stateMachine;
		void Move();
		void JumpAndHover();
	public:
		Player(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage), m_moveSpeed(20.0f), line(stage, 10, 2.0f)
			, m_bombPoint(Vec3(0.0f)), m_jumpVerocity(Vec3(0.0f, 10.0f, 0.0f))
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		void OnUpdate()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		void OnCollisionExcute(shared_ptr<GameObject>& other)override;
		void OnCollisionExit(shared_ptr<GameObject>& other)override;

		const unique_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_stateMachine;
		}

		void BulletAim();
		void BombAim();
		void BulletLaunch();
		void BombLaunch();
		void SpecialSkill();
	};

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
}
