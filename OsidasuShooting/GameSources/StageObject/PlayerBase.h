/*!
@file   PlayerBase.h
@brief  プレイヤー
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
		 * @brief ノックバックデータ
		 */
		struct KnockBackData {
			/**
			 * @brief ノックバックのタイプ
			 */
			enum class Category {
				Bullet,	// 弾
				Bomb	// 爆弾
			};

			// タイプ
			Category Type;
			// ノックバック方向
			Vec3 Direction;
			// ノックバック量
			float Amount;
			// 加害者
			weak_ptr<PlayerBase> Aggriever;

			// コンストラクタ
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
		// 初期位置
		Vec3 m_initialPosition;
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
		// 弾用のタイマー
		TimeCounter m_bulletTimer;
		// アーマー回復開始までの時間
		TimeCounter m_armorRecoveryTimer;
		// 爆弾のリロードタイマー
		TimeCounter m_bombReload;
		// 爆弾の個数
		int m_bombCount;
		// アーマーが回復中か
		bool m_isRestoreArmor;
		// ジャンプ＆ホバーステート用の連続押し検出用フラグ
		// (Stateはシングルトンであり状態が共有されてしまうため)
		bool m_isInput;
		// プレイヤーナンバー
		PlayerNumber m_playerNumber;

		// 加害者（自分に攻撃を当てたプレイヤー）
		weak_ptr<PlayerBase> m_aggriever;
		// 復帰中か
		bool m_isDuringReturn;
		// 復帰した判定を少し遅らせるためのタイマー
		TimeCounter m_returnTimer;
		// 接地判定用
		GroundingDecision m_groundingDecision;
		// 自分がプレイヤーを倒した数
		int m_countKilledPlayer;

		// 前回の正面方向
		Vec3 m_lastFrontDirection;

		// 移動
		void Move();
		// 弾の照準と発射
		void BulletAimAndLaunch();
		// 弾の照準補正
		Vec3 BulletAimCorrection(const Vec3& launchDirection);
		/**
		 * @brief 視野範囲内にpositionがあるかどうか
		 *
		 * @param direction 照準方向
		 * @param position 位置
		 * @return trueなら存在する
		 */
		bool InViewRange(const Vec3& aimDirection, const Vec3& position);
		// 爆弾の照準
		void BombAim();
		// 爆弾のリロード
		void BombReload();
		// ジャンプ
		void Jump();
		// ホバー
		void Hover();
		// ホバー可能時間回復
		void HoverTimeRecovery();
		// アーマーの回復
		void ArmorRecovery();
		// 爆弾の発射
		void BombLaunch();
		// 必殺技の発動
		void SpecialSkill();
		// 特定の方向に正面を向ける
		void TurnFrontToDirection(const Vec3& direction);
	protected:
		// 移動速度（どちらかというとかける力）
		float m_moveSpeed;
		// ジャンプ速度
		Vec3 m_jumpVerocity;
		// ホバー可能時間
		float m_hoverTime;
		// デフォルトのアーマー値
		float m_defaultArmorPoint;
		// デフォルトの爆弾の所持数
		int m_defaultBombCount;
		// 補正する角度（弾の照準）
		float m_correctAngle;
		// 入力データ
		PlayerInputData m_inputData;
		// 入力の更新
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
			// 以下のタグを持つオブジェクトを判定から除外
			m_groundingDecision.AddNotDecisionTag(L"Bomb");
			m_groundingDecision.AddNotDecisionTag(L"Bullet");
		}
		void OnCreate()override;
		void OnUpdate()override;

		// ノックバック
		void KnockBack(const KnockBackData& data);
		//リスポーン
		void Respawn();
		// テスト関数
		void TestFanc();

		/**
		 * @brief プレイヤーの番号を取得する
		 *
		 * @return プレイヤーナンバー
		 */
		PlayerNumber GetPlayerNumber() {
			return m_playerNumber;
		}

		/**
		 * @brief アーマーの(現在値 / 最大値)を取得する
		 *
		 * @return (現在値 / 最大値)
		 */
		float GetArmorPointRate() {
			return m_currentArmorPoint / m_defaultArmorPoint;
		}

		/**
		 * @brief ホバー可能時間の(現在値 / 最大値)を取得する
		 *
		 * @return (現在値 / 最大値)
		 */
		float GetHoverTimeRate() {
			return m_currentHoverTime / m_hoverTime;
		}

		/**
		 * @brief 爆弾のリロードの時間の割合を取得する
		 *
		 * @return爆弾のリロードの時間の割合
		 */
		float GetBombReloadRate() {
			return m_bombReload.GetTimeRate();
		}

		/**
		 * @brief 爆弾の残弾数を取得する
		 *
		 * @return 爆弾の残弾数
		 */
		int GetBombCount() {
			return m_bombCount;
		}

		/**
		 * @brief プレイヤーを倒した
		 */
		void KilledPlayer() {
			m_countKilledPlayer++;
		}

		/**
		 * @brief プレイヤーを倒した数を取得
		 *
		 * @return プレイヤーを倒した数
		 */
		int GetCountKilledPlayer() {
			return m_countKilledPlayer;
		}

		void SetColor(const Col4& color) {
			GetComponent<PNTStaticDraw>()->SetDiffuse(color);
		}
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
			PlayerJumpState() {}
		public:
			static shared_ptr<PlayerJumpState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj)override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj)override;
		};
		// ホバー
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
