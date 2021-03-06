/*!
@file   PlayerBase.h
@brief  プレイヤー
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
#include "Item_.h"
#include "Utility/PlayerStatus.h"

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
		// 撃つかどうか
		bool IsFire;

		// 爆弾モードへの切り替え（爆弾の発射も兼ねる）
		bool IsSwitchBombMode;
		// ジャンプorホバー
		bool IsJumpOrHover;
		// タックルモードか
		bool IsTackleMode;

		PlayerInputData() {
			this->MoveDirection = Vec3(0.0f);
			this->BulletAim = Vec3(0.0f);
			this->BombAim = Vec3(0.0f);
			this->IsFire = false;
			this->IsSwitchBombMode = false;
			this->IsJumpOrHover = false;
			this->IsTackleMode = false;
		}
	};

	/**
	 * @brief ノックバックデータ
	 */
	struct KnockBackData {
		/**
		 * @brief ノックバックのタイプ
		 */
		enum class Category {
			Bullet, // 弾
			Bomb    // 爆弾
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
		friend class PlayerStatus;
		// 初期位置
		Vec3 m_initialPosition;
		// 武器用ステートマシーン
		unique_ptr<StateMachine<PlayerBase>> m_weaponStateMachine;
		// ジャンプとホバー用のステートマシン
		unique_ptr<StateMachine<PlayerBase>> m_jumpAndHoverStateMachine;
		// リスポーン用のステートマシン
		unique_ptr<StateMachine<PlayerBase>> m_respawnStateMachine;
		// 予測線表示クラス
		PredictionLine m_predictionLine;
		// 爆弾の着弾ポイント
		Vec3 m_bombPoint;
		// 現在のエネルギー値
		float m_currentEnergy;
		// 弾用のタイマー
		TimeCounter m_bulletTimer;
		// 爆弾のリロードタイマー
		TimeCounter m_bombCoolTimeTimer;
		// 爆弾の個数
		int m_bombCount;
		// 爆弾の最大個数
		int m_maxBombCount;
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
		// 死んだ回数
		int m_deadCount;

		// 前回の正面方向
		Vec3 m_lastFrontDirection;

		bool m_debug;

		// 爆弾モードか
		bool m_isBombMode;
		// ホバーモードか
		bool m_isHoverMode;
		// 移動エフェクトのタイマー
		TimeCounter m_smokeTimer;
		// 無敵タイマー
		TimeCounter m_invincibleTimer;
		// 一定時間後にリスポーンするためのタイマー
		TimeCounter m_respawnTimer;
		// タックル用のタイマー
		TimeCounter m_tackleTimer;
		// タックル中か
		bool m_isDuringTackle;

		//色
		Col4 m_color;
		// 無敵か
		bool m_isInvincible;

		// 自身のプレイヤータイプ
		PlayerType m_playerType;

		// 弾の威力
		float m_bulletPower;
		// 爆弾の威力
		float m_bombPower;
		// 弾の発射に必要なエネルギー（1発あたり）
		float m_energyRequiredInBulletLaunch;
		// ホバーに必要なエネルギー（1秒あたり）
		float m_energyRequiredInHover;
		// 重さ
		float m_weight;
		// 弾の予測線の長さ
		float m_bulletAimLineLength;

		// アクティブかどうか
		bool m_isActive;

		// 現在の重力
		float m_currentGravity;

		// アイテムを取得したときに呼ばれる関数
		function<void(modifiedClass::ItemType)> m_itemCallback;
		function<void(int)> m_addBombForRemainCB;

		// 移動
		void Move();
		// 弾の照準発射
		Vec3 BulletAim();
		// 弾の発射
		void BulletLaunch(const Vec3& bulletAim);
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
		// ジャンプ
		void Jump();
		// ホバー
		void Hover();
		// タックル
		void Tackle();
		// エネルギーの回復
		void EnergyRecovery();
		// 爆弾の発射
		void BombLaunch();
		//// 必殺技の発動
		// void SpecialSkill();
		//  特定の方向に正面を向ける
		Vec3 TurnFrontToDirection(const Vec3& direction);
		// ホバー停止時の処理
		void StopHover();
		// 無敵処理
		void Invincible();
		/**
		 * @brief エネルギーを減らす（残量 < 減らす量の場合何もしない）
		 *
		 * @param amount 減らす量
		 * @return 減らせるかどうか
		 */
		bool DecrementEnergy(float amount);
		// パラメータのリセット
		void ParameterReset();
		/**
		 * @brief 吹っ飛びのエフェクト描画
		 */
		void KnockBackEffectDrawing();
		// 通常時の更新処理
		void NormalInit();
		// 通常時の更新処理
		void NormalUpdate();
		// 死んだときの初期化処理
		void DiedInit();
		// リスポーン時の初期化処理
		void RespawnInit();
		// アイテムの効果の処理
		bool ItemEffect(modifiedClass::ItemType type);
		// レイの判定
		Vec3 RayHitPosition(const Vec3& pos);
	protected:
		// 移動速度（どちらかというとかける力）
		float m_moveSpeed;
		// ジャンプ速度
		Vec3 m_jumpVerocity;
		// デフォルトのエネルギー値
		float m_defaultEnergy;
		// デフォルトの爆弾の所持数
		int m_defaultBombCount;
		// アーマーが0の時のノックバック倍率
		float m_armorZeroWhenKnockBackMagnification;
		// エネルギーの回復速度
		float m_energyRecoveryAmount;
		// 爆弾の照準の移動速度
		float m_bombAimMovingDistance;
		// 補正する角度（弾の照準）
		float m_correctAngle;
		// シールドが使えるエネルギーの割合
		float m_shieldRate;
		// プレイヤーのモデル
		weak_ptr<PlayerModel> m_model;
		// ノックバック時のコールバック
		function<void(float)> m_knockBackCallback;
		function<void(void)> m_bumperCallback;
		// 入力データ
		PlayerInputData m_inputData;
		// 入力の更新
		virtual void InputUpdate() = 0;
		// リスポーン時の追加処理
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

		// ノックバック
		float KnockBack(const KnockBackData& data);
		// 死亡
		void Died();

		void SetActive(bool flg);
		bool GetActive() {
			return m_isActive;
		}

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
		 * @brief プレイヤーのタイプを取得
		 *
		 * @return プレイヤータイプ
		 */
		PlayerType GetPlayerType() {
			return m_playerType;
		}

		/**
		 * @brief Energyの(現在値 / 最大値)を取得する
		 *
		 * @return (現在値 / 最大値)
		 */
		float GetEnergyRate() {
			return m_currentEnergy / m_defaultEnergy;
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
		 * @brief 爆弾の残弾を追加する
		 *
		 * @param num 追加する残弾数
		 */
		void AddBombCountForRemain30(int num);

		/**
		 * @brief 爆弾のクールタイムの割合を取得
		 *
		 * @return クールタイムの割合
		 */
		float GetBombCoolTimeRate() {
			return m_bombCoolTimeTimer.GetTimeRate();
		}

		/**
		 * @brief プレイヤーを倒した
		 */
		void KilledPlayer() {
			auto gameStage = GetTypeStage<GameStage>(false);
			if (gameStage) {
				if (gameStage->GetCurrentGameState() == GameStage::GameState::PLAYING) {
					m_countKilledPlayer++;
				}
			}
			else {
				m_countKilledPlayer++;
			}
		}

		/**
		 * @brief プレイヤーを倒した数を取得
		 *
		 * @return プレイヤーを倒した数
		 */
		int GetCountKilledPlayer() {
			return m_countKilledPlayer;
		}

		/**
		 * @brief 死んだ回数を取得
		 *
		 * @return 死んだ回数
		 */
		int GetDeadCount() {
			return m_deadCount;
		}

		/**
		 * @brief 色を取得
		 *
		 * @return 色
		 */
		Col4 GetColor() {
			return m_color;
		}

		/**
		 * @brief 爆弾モードか
		 *
		 * @return trueならそう
		 */
		bool IsBombMode() {
			return m_isBombMode;
		}
		/**
		 * @brief ホバーモードか
		 *
		 * @return trueならそう
		 */
		bool IsHoverMode() {
			return m_isHoverMode;
		}

		/**
		 * @brief 無敵か
		 *
		 * @return trueならそう
		 */
		bool IsInvincible() {
			return m_isInvincible;
		}

		/**
		 * @brief 正面方向の取得
		 *
		 * @return 正面方向のベクトル
		 */
		Vec3 GetDirectionToFace() {
			return m_lastFrontDirection;
		}

		/**
		 * @brief 現在の速度を取得
		 *
		 * @return 現在の速度
		 */
		Vec3 GetVelocity() {
			return GetComponent<PhysicalBehavior>()->GetVelocity();
		}

		/**
		 * @brief アイテム取得時のコールバックを設定
		 *
		 * @param func 関数
		 */
		void SetItemCallback(function<void(modifiedClass::ItemType)> func) {
			m_itemCallback = func;
		}

		void SetAddBombForRemainCB(function<void(int)> func) {
			m_addBombForRemainCB = func;
		}

	private:
#pragma region RespawnState
		// 通常時のステート
		class PlayerNormalState :public ObjState<PlayerBase> {
			PlayerNormalState() {}
		public:
			static shared_ptr<PlayerNormalState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
		// 死亡時のステート
		class PlayerDiedState :public ObjState<PlayerBase> {
			PlayerDiedState() {}
		public:
			static shared_ptr<PlayerDiedState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
#pragma endregion

		// 武器用ステート
#pragma region WeaponState
		// 弾の照準や発射状態（デフォルト）
		class PlayerBulletModeState : public ObjState<PlayerBase> {
			PlayerBulletModeState() {}

		public:
			static shared_ptr<PlayerBulletModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};

		// 爆弾の照準や発射状態
		class PlayerBombModeState : public ObjState<PlayerBase> {
			PlayerBombModeState() {}

		public:
			static shared_ptr<PlayerBombModeState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
#pragma endregion

		// ジャンプとホバー用のステート
#pragma region JumpAndHoverState
		// ジャンプ（デフォルト）
		class PlayerJumpState : public ObjState<PlayerBase> {
			PlayerJumpState() {}

		public:
			static shared_ptr<PlayerJumpState> Instance();
			virtual void Enter(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerBase>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerBase>& Obj) override;
		};
		// ホバー
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
