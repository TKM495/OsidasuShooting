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

	// CharacterSelect�̕����̉摜
	class CharacterStringUI : public BaseSprite {

	public:
		CharacterStringUI (const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// �P�b�e�C�̕����̉摜
	class DecisionSpriteUI : public BaseSprite {

	public:
		DecisionSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// �L�����Z���̕����̉摜
	class CancelSpriteUI : public BaseSprite {

	public:
		CancelSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// A�̉摜
	class AButtonSpriteUI : public BaseSprite {

	public:
		AButtonSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// B�̉摜
	class BButtonSpriteUI : public BaseSprite {

	public:
		BButtonSpriteUI(const shared_ptr<Stage>& stage) : BaseSprite (stage)
		{}
		void OnCreate() override;
	};

	// ReadyToFight!!�̉摜
	class ReadyToFightUI : public BaseSprite {

	public:
		ReadyToFightUI(const shared_ptr<Stage>& stage) : BaseSprite(stage)
		{}
		void OnCreate() override;
	};

	// OK!�̉摜
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