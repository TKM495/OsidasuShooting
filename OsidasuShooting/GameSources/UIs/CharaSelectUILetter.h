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
	public:
		BaseSprite(
			const shared_ptr<Stage>& stage
		) :
			GameObject(stage),
			m_sideSize(0),
			m_fSidSize(0),
			m_highSize(0),
			m_fHigSize(0),
			m_scale(0)
		{}

		virtual void CreateSprite(wstring textureKey,float sideSize,float fSidSize,float highSize,float fHigSize);
		virtual void SettingScale(float sizes);
		virtual void SettingSenter();

	};

	// CharacterSelectの文字の画像
	class CharacterStringUI : public BaseSprite {

	public:
		CharacterStringUI (const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// ケッテイの文字の画像
	class DecisionSpriteUI : public BaseSprite {

	public:
		DecisionSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// キャンセルの文字の画像
	class CancelSpriteUI : public BaseSprite {

	public:
		CancelSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// Aの画像
	class AButtonSpriteUI : public BaseSprite {

	public:
		AButtonSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// Bの画像
	class BButtonSpriteUI : public BaseSprite {

	public:
		BButtonSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// ReadyToFight!!の画像
	class ReadyToFightUI : public BaseSprite {

	public:
		ReadyToFightUI(const shared_ptr<Stage>& stage) : BaseSprite(stage)
		{}
		void OnCreate() override;
	};

	// OK!の画像
	class OKSpriteUI : public BaseSprite {
		Vec3 m_position;
	public:
		OKSpriteUI(
			const shared_ptr<Stage>& stage,
			const Vec3 position
		) :
			BaseSprite(stage),
			m_position(position)
		{}
		void OnCreate() override;
	};
}