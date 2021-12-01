/*!
@file CharaSelectUISprites.h
@brief キャラクターセレクトのUI
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

		int m_characterId;	// enumで設定
		int m_enumLength;	// enumの最大値CharacterIcon
		float m_movePos;	// キャラ(モデルおよびアイコン)一体分
		bool m_isSetStick;	// キャラクターセレクト用

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