#include "stdafx.h"
#include "Project.h"

namespace basecross {
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPCTGaugeSprite)
		IMPLEMENT_DX11_VERTEX_SHADER(VSPCTGaugeSprite, App::GetApp()->GetShadersPath() + L"VSPCTGaugeSprite.cso")
		IMPLEMENT_DX11_PIXEL_SHADER(PSPCTGaugeSprite, App::GetApp()->GetShadersPath() + L"PSPCTGaugeSprite.cso")

		PCTGaugeSprite::PCTGaugeSprite(const shared_ptr<GameObject>& gameObjectPtr)
		:MySpriteBaseDraw(gameObjectPtr), m_rate(0.0f), m_threshold(0.05f)
	{
		// �p�C�v���C���X�e�[�g���f�t�H���g��2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}

	PCTGaugeSprite::PCTGaugeSprite(const shared_ptr<GameObject>& gameObjectPtr,
		vector<VertexPositionColorTexture>& vertices, vector<uint16_t>& indices)
		:MySpriteBaseDraw(gameObjectPtr), m_rate(0.0f), m_threshold(0.05f)
	{
		// �p�C�v���C���X�e�[�g���f�t�H���g��2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
		try {
			CreateMesh(vertices, indices);
		}
		catch (...) {
			throw;
		}
	}

	void PCTGaugeSprite::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//�쐬����ĂȂ�������쐬����
			float HelfSize = 0.5f;
			//���_�z��
			vector<VertexPositionColorTexture> vertices = {
				{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 1.0f)) },
			};
			//�C���f�b�N�X�z��
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//���b�V���̍쐬�i�ύX�ł���j
			CreateMesh(vertices, indices);
		}
	}

	void PCTGaugeSprite::OnDraw() {
		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::CullNone);
		}
		//���b�V�����\�[�X�̎擾
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//�V�F�[�_�̐ݒ�
			DrawSprite(PtrMeshResource->GetMashData());
		}
		//��n��
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

	void PCTGaugeSprite::DrawSprite(const MeshPrimData& data) {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//NULL�̃V�F�[�_���\�[�X�̏���
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		//�T���v���[�̏���
		ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
		//�e�I�u�W�F�N�g���ʏ���
		//�V�F�[�_�̐ݒ�
		//���_�V�F�[�_
		pD3D11DeviceContext->VSSetShader(VSPCTGaugeSprite::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPCTGaugeSprite::GetPtr()->GetInputLayout());
		//�s�N�Z���V�F�[�_
		pD3D11DeviceContext->PSSetShader(PSPCTGaugeSprite::GetPtr()->GetShader(), nullptr, 0);
		//�ʏ���
		GaugeSpriteConstants sb;
		//�R���X�^���g�o�b�t�@�̍쐬
		SetConstants(sb);
		//�e�N�X�`��
		auto shTex = GetTextureResource();
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBPCTGaugeSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBPCTGaugeSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = data.m_NumStride;
		UINT offset = 0;
		//�`����@�̃Z�b�g
		pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
		//���_�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		//�e�����_�����O�X�e�[�g�̐ݒ�
		//�u�����h�X�e�[�g
		RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
		//�f�v�X�X�e���V���X�e�[�g
		RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
		//�e�N�X�`���ƃT���v���[
		if (shTex) {
			pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//�T���v���[��ݒ�
			RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
		}
		else {
			//�V�F�[�_�[���\�[�X���N���A
			pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//�T���v���[���N���A
			RenderState->SetSamplerAllClear(pD3D11DeviceContext);
		}
		//���X�^���C�U�X�e�[�g�ƕ`��
		RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
		//�`��
		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	}

	void PCTGaugeSprite::SetConstants(GaugeSpriteConstants& spCb) {
		// �s��̎擾
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		// �s��̒�`
		Mat4x4 World, Proj;
		World = PtrTrans->Get2DWorldMatrix();
		// �ˉe�s��̌���
		GetGameObject()->OnGet2DDrawProjMatrix(Proj);
		// �s��̍���
		World *= Proj;
		// �G�~�b�V�u
		spCb.Emissive = GetEmissive();
		// �f�t�B�[�Y�͂��ׂĒʂ�
		spCb.Diffuse = GetDiffuse();
		// �s��̐ݒ�
		spCb.World = World;
		spCb.RatioAndThreshold = Vec4(m_rate, m_threshold, 0.0f, 0.0f);
	}
}