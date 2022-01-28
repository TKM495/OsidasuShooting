/*!
@file CharaSelectUILetter.h
@brief キャラクターセレクト画面の文字UI
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"

namespace basecross
{
	class BaseSprite : public GameObject {
		wstring m_textureKey;
		vector<VertexPositionColorTexture> vertices;

		float m_sideSize;		// 使用する横幅
		float m_fSidSize;		// 画像の横幅(画像の一部分だけ使う時の物)
		float m_highSize;		// 使用する縦幅
		float m_fHigSize;		// 画像の縦幅(画像の一部分だけ使う時の物)
		float m_zeroSize = 0;	// 0
		float m_oneSize  = 1;	// 1
		float m_quatSize = 0.25f;	// 1/4
		float m_helfSize = 0.5f;	// 1/2
		float m_tqatSize = 0.75f;	// 3/4

		Vec3 m_scale;
		Vec3 m_setPos;
		Col4 m_setColor;

	public:
		BaseSprite(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			GameObject(stage),
			m_setPos(setPosition),
			m_sideSize(0),
			m_fSidSize(0),
			m_highSize(0),
			m_fHigSize(0),
			m_scale(0),
			m_setColor{0}
		{}

		virtual void CreateSprite(wstring textureKey,float sideSize,float highSize);
		virtual void SettingScale(Vec3 scale);
		virtual void SettingPositionSenter(Vec3 position);
		virtual void SettingPivot();

	};

	// CharacterSelectの文字の画像
	class CharacterStringUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		CharacterStringUI (
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite (stage,setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// ケッテイの文字の画像
	class DecisionSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		DecisionSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// キャンセルの文字の画像
	class CancelSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		CancelSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// 戻るの文字の画像
	class GoToTitleSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		GoToTitleSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// 進むの文字の画像
	class GoToSelectSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		GoToSelectSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// Aの画像
	class AButtonSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		AButtonSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// Bの画像
	class BButtonSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		BButtonSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// ReadyToFight!!の画像
	class ReadyToFightUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		ReadyToFightUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// OK!の画像
	class OKSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		OKSpriteUI(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// Iconの画像
	class CharaIcon : public BaseSprite {
		Vec3 m_setPos;
		int m_iconNumber;
	public:
		CharaIcon(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition,
			int iconNumber
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_iconNumber(iconNumber)
		{}
		void OnCreate() override;
		void OnUpdate() override;
	};

	// SelectCursorのスプライト
	//class SelectCursor : public BaseSprite {
	//	Vec3 m_setPos;		// 初期位置
	//	Vec3 m_nowPos;		// 今カーソルがあるポジション
	//	Vec3 m_iconPos[2];	// アイコンの位置

	//	int m_gamePadID;	// 操作するゲームパッドの番号
	//	int m_iconNumber;	// 今カーソルがあるアイコンのナンバー
	//	int m_iconMaxNumber;// アイコンの最大値 

	//	float m_moveTime;	// 次のアイコンに移動するまでにかかった時間
	//	float m_moveSpeed;  // 移動時間

	//	bool m_isRightStick;// スティックが右に倒されているかどうか
	//	bool m_isSetStick;	// スティックが倒されているかどうか

	//	bool m_waitAnime;

	//public:
	//	SelectCursor(
	//		const shared_ptr<Stage>& stage,
	//		const Vec3 setPosition,
	//		int gamePadID
	//	) :
	//		BaseSprite(stage, setPosition),
	//		m_setPos(setPosition),
	//		m_iconPos{},
	//		m_gamePadID(gamePadID),
	//		m_iconNumber(),
	//		m_iconMaxNumber(),
	//		m_moveTime(),
	//		m_moveSpeed(4.0f),
	//		m_isRightStick(false),
	//		m_isSetStick(false),
	//		m_waitAnime(false)
	//	{}
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	// コントローラの入力
	//	void CursorController();// 入力
	//	void CursorControl();	// 処理
	//	// アイコンのそれぞれの位置とアイコンの最大値
	//	void GetIconDatas(int number,Vec3 pos);
	//	// カーソルを移動させる
	//	void MoveCursor();
	//	// アニメーション
	//	void WaitAnimetion();
	//	void NotMoveAnimetion();
	//	//
	//	int SetCharacterID();
	//	Vec3 GetIconPos(int number);
	//};

	// ステータス項目の画像
	class StatusSpriteUI : public BaseSprite {
		Vec3 m_setPos;
		int m_spriteNumber;
	public:
		StatusSpriteUI(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition,
			int spriteNumber
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_spriteNumber(spriteNumber)
		{}
		void OnCreate()  override;
		Col4 StetusColor();
	};

	// ステータス項目のゲージ
	class StatusGauge : public BaseSprite {
		Vec3 m_setPos;			// 配置位置
		Vec3 m_setScale;		// ゲージを動かす
		int m_gamePadID;		// 何番目のプレイヤーのゲージかを判別するための物
		int m_spriteNumber;		// どの項目かパワー、スピード、ウェイトの順
		float m_defaultGauge;	// ゲージの1割
		float m_setStutas;		// 選択中のキャラクターのステータスを対応させる
		float m_power;			// 一撃の威力
		float m_speed;			// 移動速度と射撃速度
		float m_weight;			// 落下速度と耐久力

		//Easing(エージングに使用する変数)
		Vec3 m_beforeScale;		// 前のスケール
		int m_beforeCharaNum;	// 比較用
		int m_nowCharaNum;		//
		float m_beforeStatus;	// 前のステータス
		float m_easingTime;		// イージングの経過時間
		float m_easingAllTime;	// イージングの終了時間

		//shared_ptr<SelectCursor> m_selectCursor; // カーソル
	public:
		StatusGauge(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition,
			const int gamePadID,
			int spriteNumber
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_setScale(),
			m_gamePadID(gamePadID),
			m_spriteNumber(spriteNumber),
			m_defaultGauge(),
			m_setStutas(),
			m_power(), m_speed(), m_weight(),
			
			m_beforeScale(),
			m_beforeCharaNum(),
			m_nowCharaNum(),
			m_beforeStatus(),
			m_easingTime(0),
			m_easingAllTime(0.25f)
		{}
		void OnCreate() override;
		void OnUpdate() {};

		// キャラクターのステータス
		void GetCharaStutas(int charaNumber, int stutasNumber);

		// レーザーのステータス
		float GetLaserStutas(int stutasNumber);
		// タンクのステータス
		float GetTankStutas (int stutasNumber);
		// 未使用
		//void SetCharaStutas(float power, float speed, float weight);

	};

	// ゲージの後ろ
	class StatusGaugeBack : public BaseSprite {
		Vec3 m_setPos;
	public:
		StatusGaugeBack(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// 
	class TriangleSprite : public BaseSprite {
		Vec3 m_setPos;
		float m_defPos;

		const float m_movePos;

		bool m_filstLoad;
		bool m_isReTriangle;
	public:
		TriangleSprite(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition,
			bool isReTriangle
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_defPos(),
			m_movePos(9),
			m_isReTriangle(isReTriangle),
			m_filstLoad(false)
		{}
		void OnCreate() override;
		void CharacterSelectingAnimation(const CONTROLER_STATE& getStick,bool stick, bool left, bool right,int gamePadID);
	};
}