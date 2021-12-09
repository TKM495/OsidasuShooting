/*!
@file CharaSelectUILetter.h
@brief キャラクターセレクト画面の文字UI
*/

#pragma once
#include "stdafx.h"

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

		float m_scale;
		Vec3 m_setPos;
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
			m_scale(0)
		{}

		virtual void CreateSprite(wstring textureKey,float sideSize,float fSidSize,float highSize,float fHigSize);
		virtual void SettingScale(float sizes);
		virtual void SettingPosition(Vec3 position);

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
	class BackSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		BackSpriteUI(
			const shared_ptr<Stage>& stage,
			Vec3 setPosition
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition)
		{}
		void OnCreate() override;
	};

	// 進むの文字の画像
	class NextSpriteUI : public BaseSprite {
		Vec3 m_setPos;
	public:
		NextSpriteUI(
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
		void OnUpdate() override;
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
}