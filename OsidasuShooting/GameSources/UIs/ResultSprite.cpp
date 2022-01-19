/*!
@file ResultSprite.cpp
@brief リザルトで使うスプライトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ResultWinnerSprite::OnCreate() {
		//texture 512 x 256
		float sideSize = 512.0f;
		float highSize = -256.0f;
		float zeroSize = 0.0f;
		float oneSize = 1.0f;
		float quatSize = 0.25f;
		float helfSize = 0.5f;
		float tqatSize = 0.75f;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		// ポリゴンの頂点データ
		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(zeroSize, zeroSize, zeroSize),color,Vec2(zeroSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(sideSize, zeroSize, zeroSize),color,Vec2( oneSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(zeroSize, highSize, zeroSize),color,Vec2(zeroSize,  oneSize))},
			{VertexPositionColorTexture(Vec3(sideSize, highSize, zeroSize),color,Vec2( oneSize,  oneSize))}
		};

		// 頂点インデックス
		vector<uint16_t> indeces = {
			0, 1, 2,
			1, 3, 2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indeces);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey); // Stage側で設定

		SetAlphaActive(true);

		// 位置、拡大縮小
		auto ptrTrans = GetComponent<Transform>();
		Vec3 senterPos(sideSize * helfSize, highSize * helfSize, 0);
		Vec3 pos(-280,-220,0);
		Vec3 scl(1);
		ptrTrans->SetPosition(pos - senterPos);
		ptrTrans->SetScale(scl);

	}

	void KillIcon::OnCreate() {
		auto texture = L"Kill";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	void DeadIcon::OnCreate() {
		auto texture = L"Dead";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}
}