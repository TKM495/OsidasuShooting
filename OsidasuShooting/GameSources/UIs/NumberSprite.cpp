/*!
@file NumberSprite.cpp
@brief 数字のスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Number::OnCreate() {
		//texture 640 x 128
		//font 64 x 128
		float sideSize = 704.0f;
		float fSidSize = 1024.0f; //fullSideSize、全体の横の長さ
		float highSize = -128.0f;
		float fontSize = 64.0f;
		float zeroSize = 0.0f;
		float  oneSize = 1.0f;
		float quatSize = 0.25f;
		float helfSize = 0.5f;
		float tqatSize = 0.75f;

		float setNumber = static_cast<float>(m_number);
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		// ポリゴンの頂点データ
		vertices = {
			{VertexPositionColorTexture(Vec3(zeroSize, zeroSize, zeroSize),color,Vec2((setNumber + zeroSize) * fontSize / fSidSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(fontSize, zeroSize, zeroSize),color,Vec2((setNumber +  oneSize) * fontSize / fSidSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(zeroSize, highSize, zeroSize),color,Vec2((setNumber + zeroSize) * fontSize / fSidSize,  oneSize))},
			{VertexPositionColorTexture(Vec3(fontSize, highSize, zeroSize),color,Vec2((setNumber +  oneSize) * fontSize / fSidSize,  oneSize))}
		};

		// 頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		//ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		//ptrDraw->SetTextureResource(m_textureKey); // TitleStage側で設定
		ptrDraw->SetTextureResource(L"Number"); // 直接設定

		SetAlphaActive(true);

		// 位置、拡大縮小 表示用
		auto ptrTrans = GetComponent<Transform>();
		//Vec3 pos(-sideSize * helfSize * tqatSize, -highSize * tqatSize * tqatSize, zeroSize);
		//Vec3 scl(oneSize, oneSize, oneSize);
		//ptrTrans->SetPosition(pos);
		//ptrTrans->SetScale(scl);
	};
}