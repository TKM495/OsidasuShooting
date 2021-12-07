/*!
@file CharaSelectUISprites.h
@brief �L�����N�^�[�Z���N�g��ʂ�UI
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

		int m_characterId;	// enum�Őݒ�
		int m_enumLength;	// enum�̍ő�lCharacterIcon
		bool m_isSetStick;	// �L�����N�^�[�Z���N�g�p

		int m_gamePadID;	// �R���g���[���p
		float m_movePos;	// �L����(���f������уA�C�R��)��̕��ړ�����l
		Vec3 m_position;	// �|�W�V�����A�A�C�R�����\���ɂ��邩�̏��̂��߂Ɏ擾

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

		void CreateSprite();		// �|�������

		void CharacterSelecting();	// �X�e�B�b�N�A�����p�b�h�ŃA�C�R�����ς��悤�ɂ���
		void IconsDraw();			// �\������A�C�R��
	};

	class SelectTriangle : public CharacterIcon {
		Vec3 m_scale;
		Vec3 m_rotation;
		bool m_isInversion;

		int m_characterId;	// enum�Őݒ�
		float m_movePos;	// �O�p�̃A�j���[�V����
		float m_defPos;		// �����ʒu

		bool m_isSetStick;	// �L�����N�^�[�Z���N�g�p
		bool m_setDefPos;

		int m_gamePadID;	// �R���g���[���p

	public:
		SelectTriangle(
			const shared_ptr<Stage>& stage,	// �X�e�[�W
			const wstring textureKey,		// �e�N�X�`��
			const int gamePadID,			// �Q�[���p�b�h�̏��(�R���g���[�����Ƃɑ���ł���悤�Ɏg�p)
			float iconShift,				// �A�C�R���̈ړ�����l(�ݒu�ȂǂŎg�p)
			Vec3 position,					// �ʒu
			Vec3 scale,						// �g��k��
			bool isInversion				// ���]���Ă��邩�ǂ���
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

		void CharacterSelecting();	// �X�e�B�b�N�A�����p�b�h�ŃA�j���[�V��������


	};

}