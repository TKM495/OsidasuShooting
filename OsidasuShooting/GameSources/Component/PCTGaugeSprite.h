#pragma once
#include "stdafx.h"

namespace basecross {
	struct GaugeSpriteConstants
	{
		// ���[���h�s��
		Mat4x4 World;
		// �G�~�b�V�u�F
		Col4 Emissive;
		// �f�t���[�Y�F
		Col4 Diffuse;
		// �����Ƃ������l
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
		 * @brief �R���X�^���g�o�b�t�@�̐ݒ�
		 *
		 * @param spCb �ݒ肷��R���X�^���g�o�b�t�@�\����
		 */
		void SetConstants(GaugeSpriteConstants& spCb);

		/**
		 * @brief �X�v���C�g���b�V���̕`��
		 *
		 * @param data ���b�V���̃f�[�^
		 */
		void DrawSprite(const MeshPrimData& data);
	};
}
