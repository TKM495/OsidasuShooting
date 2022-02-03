/*!
@file CreateUISprite.h
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
		float m_oneSize = 1;	// 1
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
			m_setColor{ 0 }
		{}

		virtual void CreateSprite(wstring textureKey, float sideSize, float highSize);
		virtual void SettingScale(Vec3 scale);
		virtual void SettingPositionSenter(Vec3 position);
		virtual void SettingPivot();

	};
}