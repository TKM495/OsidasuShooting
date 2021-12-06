/*!
@file CharaSelectUISprites.h
@brief キャラクターセレクト画面のUI
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	enum class characters {
		Laser,
		Missile,
		char3
	};

	class CharacterIcon : public GameObject {
		wstring m_textureKey;
		Vec3 m_charaPosition;
		vector<VertexPositionColorTexture> vertices;

		int m_characterId;	// enumで設定
		int m_enumLength;	// enumの最大値CharacterIcon
		bool m_isSetStick;	// キャラクターセレクト用

		int m_gamePadID;	// コントロール用
		float m_movePos;	// キャラ(モデルおよびアイコン)一体分移動する値
		Vec3 m_position;	// ポジション、アイコンを非表示にするかの情報のために取得

	public:
		CharacterIcon(
			const shared_ptr<Stage>& stage,
			const wstring textureKey,
			const int gamePadID,
			float iconShift,
			Vec3 position
		) :
			GameObject(stage),
			m_textureKey(textureKey),
			m_enumLength(2),
			m_characterId(0),
			m_movePos(iconShift),
			m_isSetStick(false),
			m_gamePadID(gamePadID),
			m_position(position)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void CreateSprite();		// 板ポリを作る

		void CharacterSelecting();	// スティック、方向パッドでアイコンが変わるようにする
		void IconsDraw();			// 表示するアイコン
	};

	class SelectTriangle : public CharacterIcon {
		Vec3 m_scale;
		Vec3 m_rotation;
		bool m_isInversion;

		int m_characterId;	// enumで設定
		float m_movePos;	// 三角のアニメーション
		float m_defPos;		// 初期位置

		bool m_isSetStick;	// キャラクターセレクト用
		bool m_setDefPos;

		int m_gamePadID;	// コントロール用

	public:
		SelectTriangle(
			const shared_ptr<Stage>& stage,	// ステージ
			const wstring textureKey,		// テクスチャ
			const int gamePadID,			// ゲームパッドの情報(コントローラごとに操作できるように使用)
			float iconShift,				// アイコンの移動する値(設置などで使用)
			Vec3 position,					// 位置
			Vec3 scale,						// 拡大縮小
			bool isInversion				// 反転しているかどうか
		) :
			CharacterIcon(stage, textureKey, gamePadID, NULL, position),
			m_scale(scale),
			m_isInversion(isInversion),
			m_characterId(0),
			m_movePos(9),
			m_defPos(0),
			m_isSetStick(false),
			m_setDefPos(false),
			m_gamePadID(gamePadID)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void CharacterSelecting();	// スティック、方向パッドでアニメーションする


	};

}