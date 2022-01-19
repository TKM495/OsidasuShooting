/*!
@file CharaSelectUILetter.h
@brief �L�����N�^�[�Z���N�g��ʂ̕���UI
*/

#pragma once
#include "stdafx.h"
#include "StageObject/PlayerBase.h"

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
		virtual void SettingScale(Vec3 sizes);
		virtual void SettingPositionSenter(Vec3 position);

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

	// �i�ނ̕����̉摜
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

	// Icon�̉摜
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
	};

	// SelectCursor�̃X�v���C�g
	class SelectCursor : public BaseSprite {
		Vec3 m_setPos;		// �����ʒu
		Vec3 m_nowPos;		// ���J�[�\��������|�W�V����
		Vec3 m_iconPos[2];	// �A�C�R���̈ʒu

		int m_gamePadID;	// ���삷��Q�[���p�b�h�̔ԍ�
		int m_iconNumber;	// ���J�[�\��������A�C�R���̃i���o�[
		int m_iconMaxNumber;// �A�C�R���̍ő�l 

		float m_moveTime;	// ���̃A�C�R���Ɉړ�����܂łɂ�����������
		float m_moveSpeed;  // �ړ�����

		bool m_isRightStick;// �X�e�B�b�N���E�ɓ|����Ă��邩�ǂ���
		bool m_isSetStick;	// �X�e�B�b�N���|����Ă��邩�ǂ���

		bool m_waitAnime;

	public:
		SelectCursor(
			const shared_ptr<Stage>& stage,
			const Vec3 setPosition,
			int gamePadID
		) :
			BaseSprite(stage, setPosition),
			m_setPos(setPosition),
			m_iconPos{},
			m_gamePadID(gamePadID),
			m_iconNumber(),
			m_iconMaxNumber(),
			m_moveTime(),
			m_moveSpeed(4.0f),
			m_isRightStick(false),
			m_isSetStick(false),
			m_waitAnime(false)
		{}
		void OnCreate() override;
		void OnUpdate() override;

		// �R���g���[���̓���
		void CursorController();// ����
		void CursorControl();	// ����
		// �A�C�R���̂��ꂼ��̈ʒu�ƃA�C�R���̍ő�l
		void GetIconDatas(int number,Vec3 pos);
		// �J�[�\�����ړ�������
		void MoveCursor();
		// �A�j���[�V����
		void WaitAnimetion();
		void NotMoveAnimetion();
		//
		int SetCharacterID();
		Vec3 GetIconPos(int number);
	};

	// �X�e�[�^�X���ڂ̉摜
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

	// �X�e�[�^�X���ڂ̃Q�[�W
	class StatusGauge : public BaseSprite {
		Vec3 m_setPos;
		Vec3 m_setScale;
		int m_gamePadID;
		int m_spriteNumber;
		float m_defaultGauge;
		Vec3 m_power;
		Vec3 m_speed;
		Vec3 m_weight;

		shared_ptr<SelectCursor> m_selectCursor;
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
			m_power(),m_speed(),m_weight()
		{}
		void OnCreate() override;
		void OnUpdate() override;

		void GetCharaStutas(int charaNumber, int stutasNumber);
		Vec3 GetLaserStutas(int stutasNumber);
		Vec3 GetTankStutas (int stutasNumber);
		void SetCharaStutas(float power, float speed, float weight);

	};

	// �Q�[�W�̌��
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
}