/*!
@file CharaSelectUISprites.h
@brief �L�����N�^�[�Z���N�g��UI
*/

#pragma once
#include "stdafx.h"
#include "BaseUI.h"

namespace basecross
{
	enum class characters {
		Laser,
		Missile,
		char3,
		char4
	};

	class CharacterIcon : public GameObject {
		wstring m_textureKey;
		Vec3 m_charaPosition;
		vector<VertexPositionColorTexture> vertices;

		int m_characterId;	// enum�Őݒ�
		int m_enumLength;	// enum�̍ő�lCharacterIcon
		float m_movePos;	// �L����(���f������уA�C�R��)��̕�
		bool m_isSetStick;	// �L�����N�^�[�Z���N�g�p

	public:
		CharacterIcon(
			const shared_ptr<Stage>& stage,
			const wstring textureKey
		) :
			GameObject(stage),
			m_textureKey(textureKey),
			m_enumLength(3),
			m_characterId(0),
			m_movePos(200),
			m_isSetStick(false)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void CharacterSelecting();

	};

}