/*!
@file CreateUISprite.cpp
@brief キャラクターセレクト画面の文字UIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float highSize) {
		m_textureKey = textureKey;	// テクスチャ
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// テクスチャ座標でUVを定義
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};

		if (sideSize == NULL) m_sideSize = m_oneSize;
		else m_sideSize = sideSize;	// 横幅

		if (m_highSize == NULL) m_highSize = m_oneSize;
		else m_highSize = highSize;	// 縦幅

		m_fSidSize = size.x;		// 使用する画像の横幅全体
		m_fHigSize = -size.y;		// 使用する画像の縦幅全体

		m_sideSize = m_fSidSize / m_sideSize;
		m_highSize = m_fHigSize / m_highSize;

		auto color = Col4{ 1.0f };

		vector<VertexPositionColorTexture> vertices = {
			{Vec3(m_zeroSize, m_zeroSize, m_zeroSize), color, Vec2(m_zeroSize, m_zeroSize)},
			{Vec3(m_sideSize, m_zeroSize, m_zeroSize), color, Vec2(m_oneSize, m_zeroSize)},
			{Vec3(m_zeroSize, m_highSize, m_zeroSize), color, Vec2(m_zeroSize,  m_oneSize)},
			{Vec3(m_sideSize, m_highSize, m_zeroSize), color, Vec2(m_oneSize,  m_oneSize)}
		};

		vector<uint16_t> indeces = {
			0,1,2,
			1,3,2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indeces);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);

		SetAlphaActive(true);
	}

	void BaseSprite::SettingScale(Vec3 scale) {
		m_scale = scale;
		auto ptrTrans = GetComponent<Transform>();
		auto scl = m_scale;
		ptrTrans->SetScale(scl);
	}

	// ポジションをセンターに合わせる
	void BaseSprite::SettingPositionSenter(Vec3 position) {
		auto ptrTrans = GetComponent<Transform>();
		auto xSntrPos = m_sideSize * m_helfSize;
		auto ySntrPos = m_highSize * m_helfSize;

		auto pos = ptrTrans->GetPosition();
		Vec3 senterPos(xSntrPos, ySntrPos, 0);
		pos.x = (pos.x - senterPos.x * m_scale.x) + position.x;
		pos.y = (pos.y - senterPos.y * m_scale.y) + position.y;
		ptrTrans->SetPosition(pos);
	}

	// ピボットポイント設定
	void BaseSprite::SettingPivot() {
		auto ptrTrans = GetComponent<Transform>();
		auto xPivot = m_sideSize * m_helfSize;
		auto yPivot = m_highSize * m_helfSize;
		ptrTrans->SetPivot(Vec3(xPivot, -yPivot, 1.0f));
		//ptrTrans->SetPivot(GetComponent<Transform>()->GetPosition());
	}

}