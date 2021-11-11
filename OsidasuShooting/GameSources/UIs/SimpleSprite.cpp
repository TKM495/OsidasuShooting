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
		// テクスチャ座標からUV座標に変換
		Utility::ConvertToUVCoordinates(uv, m_textureKey, uvs);
		Col4 color(1.0f);
		// 頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-size.x,+size.y,0.0f),color,uvs[0]}, //0
			{Vec3(+size.x,+size.y,0.0f),color,uvs[1]}, //1

			{Vec3(-size.x,-size.y,0.0f),color,uvs[2]}, //2
			{Vec3(+size.x,-size.y,0.0f),color,uvs[3]},  //3
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

	void SimpleSprite::OnUpdate() {
	}
}