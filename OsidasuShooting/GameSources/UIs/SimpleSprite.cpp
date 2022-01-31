#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SimpleSprite::OnCreate() {
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// テクスチャ座標でUVを定義
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		halfSize = size / 2.0f;
		// テクスチャ座標からUV座標に変換
		Utility::ConvertToUVCoordinates(uv, m_textureKey, uvs);
		Col4 color(1.0f);
		// 頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfSize.x,+halfSize.y,0.0f),color,uvs[0]}, //0
			{Vec3(+halfSize.x,+halfSize.y,0.0f),color,uvs[1]}, //1

			{Vec3(-halfSize.x,-halfSize.y,0.0f),color,uvs[2]}, //2
			{Vec3(+halfSize.x,-halfSize.y,0.0f),color,uvs[3]},  //3
		};
		// 頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, // 上の三角形
			2, 1, 3  // 下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_textureKey);
		// テクスチャの繰り返し設定(Wrap)
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); // 透明をサポートする&両面描画になる
		SetDrawLayer(2);
		SetUpdateActive(false);
	}

	void BoardPoly::OnCreate() {
		auto size = Utility::GetTextureSize(m_textureKey);

		auto rate = size.y / size.x;
		size.y = rate;
		size.x = 1.0f;
		auto halfSize = size / 2.0f;

		Vec3 normal(0, 1, 0);
		// 頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionNormalTexture> vertices = {
			{Vec3(-halfSize.x,0.0f,+halfSize.y),normal,Vec2(0,0)}, //0
			{Vec3(+halfSize.x,0.0f,+halfSize.y),normal,Vec2(1,0)}, //1

			{Vec3(-halfSize.x,0.0f,-halfSize.y),normal,Vec2(0,1)}, //2
			{Vec3(+halfSize.x,0.0f,-halfSize.y),normal,Vec2(1,1)},  //3
		};
		// 頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, // 上の三角形
			2, 1, 3  // 下の三角形
		};

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetTextureResource(m_textureKey);

		SetAlphaActive(true); // 透明をサポートする&両面描画になる
		SetUpdateActive(false);
	}
}