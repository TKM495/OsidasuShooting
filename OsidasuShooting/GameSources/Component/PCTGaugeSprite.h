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
		// �����Ƃ������l�ƃt���O
		Vec4 RatioAndThresholdEtc;
		GaugeSpriteConstants() {
			memset(this, 0, sizeof(GaugeSpriteConstants));
			Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBPCTGaugeSprite, GaugeSpriteConstants)
	DECLARE_DX11_VERTEX_SHADER(VSPCTGaugeSprite, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPCTGaugeSprite)

	class PCTGaugeSprite :public MySpriteBaseDraw {
		// �����i0�`1�j
		float m_rate;
		// �������l
		float m_threshold;
		// �����ɉ������Q�[�W�̐F�ɂ���Ƃ��ɃO���f�[�V�����e�N�X�`���L�[
		wstring m_gaugeGradientTexKey;
		// �w�i���肩
		bool m_isBackground;
	public:
		explicit PCTGaugeSprite(const shared_ptr<GameObject>& gameObjectPtr);
		explicit PCTGaugeSprite(const shared_ptr<GameObject>& gameObjectPtr,
			vector<VertexPositionColorTexture>& vertices, vector<uint16_t>& indices);

		void OnCreate()override;
		void OnUpdate()override {}
		void OnDraw()override;

		/**
		 * @brief �Q�[�W�c�ʂ̐ݒ�
		 *
		 * @param rate ����
		 */
		void SetRate(float rate) {
			m_rate = rate;
		}

		/**
		 * @brief �Q�[�W�̐F�̐ݒ�
		 *
		 * @param color �Q�[�W�̐F
		 */
		void SetGaugeColor(const Col4& color) {
			SetDiffuse(color);
		}

		/**
		 * @brief �O���f�[�V�����e�N�X�`���̐ݒ�
		 *
		 * @param key
		 */
		void SetGaugeGradientTexture(const wstring& key) {
			m_gaugeGradientTexKey = key;
		}

		/**
		 * @brief �w�i�����邩
		 *
		 * @param flg true�Ȃ炠��
		 */
		void IsBackground(bool flg) {
			m_isBackground = flg;
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
