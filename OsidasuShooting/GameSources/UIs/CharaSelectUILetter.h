/*!
@file CharaSelectUILetter.h
@brief �L�����N�^�[�Z���N�g��ʂ̕���UI
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class BaseSprite : public GameObject {
		wstring m_textureKey;
		vector<VertexPositionColorTexture> vertices;

		float m_sideSize;		// �g�p���鉡��
		float m_fSidSize;		// �摜�̉���(�摜�̈ꕔ�������g�����̕�)
		float m_highSize;		// �g�p����c��
		float m_fHigSize;		// �摜�̏c��(�摜�̈ꕔ�������g�����̕�)
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

	// CharacterSelect�̕����̉摜
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

	// �P�b�e�C�̕����̉摜
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

	// �L�����Z���̕����̉摜
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

	// �߂�̕����̉摜
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

	// �i�ނ̕����̉摜
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

	// A�̉摜
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

	// B�̉摜
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

	// ReadyToFight!!�̉摜
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

	// OK!�̉摜
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