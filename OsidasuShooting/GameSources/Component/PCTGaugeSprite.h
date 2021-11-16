#pragma once
#include "stdafx.h"

namespace basecross {
	struct GaugeSpriteConstants
	{
		// ワールド行列
		Mat4x4 World;
		// エミッシブ色
		Col4 Emissive;
		// デフューズ色
		Col4 Diffuse;
		// 割合としきい値
		Vec4 RatioAndThreshold;
		GaugeSpriteConstants() {
			memset(this, 0, sizeof(GaugeSpriteConstants));
			Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBPCTGaugeSprite, GaugeSpriteConstants)
	DECLARE_DX11_VERTEX_SHADER(VSPCTGaugeSprite, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPCTGaugeSprite)

	class PCTGaugeSprite :public MySpriteBaseDraw {
		Col4 m_gaugeColor;
		float m_rate;
		float m_threshold;
	public:
		explicit PCTGaugeSprite(const shared_ptr<GameObject>& gameObjectPtr);
		explicit PCTGaugeSprite(const shared_ptr<GameObject>& gameObjectPtr,
			vector<VertexPositionColorTexture>& vertices, vector<uint16_t>& indices);

		void OnCreate()override;
		void OnUpdate()override {}
		void OnDraw()override;

		void SetRate(float rate) {
			m_rate = rate;
		}
		void SetThreshold(float threshold) {
			m_threshold = threshold;
		}
		void SetGaugeColor(const Col4& color) {
			m_gaugeColor = color;
		}
	private:
		/**
		 * @brief コンスタントバッファの設定
		 *
		 * @param spCb 設定するコンスタントバッファ構造体
		 */
		void SetConstants(GaugeSpriteConstants& spCb);

		/**
		 * @brief スプライトメッシュの描画
		 *
		 * @param data メッシュのデータ
		 */
		void DrawSprite(const MeshPrimData& data);
	};
}
