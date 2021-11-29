/*!
@file EfkInterface.cpp
@brief Effekseer�G�t�F�N�g�̃C���^�[�t�F�C�X����
*/

#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	// �ÓI�����o�ϐ��̎���
	shared_ptr<EfkInterface> EfkInterface::m_ownInstance = nullptr;

	// �C���X�^���X�̎擾
	shared_ptr<EfkInterface> EfkInterface::GetInstance() {
		if (m_ownInstance.get() == 0)
		{
			throw BaseException(
				L"EfkInterface����������Ă��܂���",
				L"if (m_ownInstance.get() == 0)",
				L"EfkInterface::GetInstance()"
			);
		}
		return m_ownInstance;
	}

	EfkInterface::EfkInterface(const shared_ptr<Stage>& stage)
		:AdvancedGameObject(stage),
		m_Manager(nullptr),
		m_Renderer(nullptr)
	{}
	EfkInterface::~EfkInterface() {}

	void EfkInterface::OnCreate() {
		m_ownInstance = nullptr;
		m_ownInstance = GetThis<EfkInterface>();

		//�f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pDx11Device = Dev->GetD3DDevice();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		// �`��p�C���X�^���X�̐���
		m_Renderer = ::EffekseerRendererDX11::Renderer::Create(pDx11Device, pID3D11DeviceContext, 2000);
		// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
		m_Manager = ::Effekseer::Manager::Create(2000);

		// �`��p�C���X�^���X����`��@�\��ݒ�
		m_Manager->SetSpriteRenderer(m_Renderer->CreateSpriteRenderer());
		m_Manager->SetRibbonRenderer(m_Renderer->CreateRibbonRenderer());
		m_Manager->SetRingRenderer(m_Renderer->CreateRingRenderer());
		m_Manager->SetTrackRenderer(m_Renderer->CreateTrackRenderer());
		m_Manager->SetModelRenderer(m_Renderer->CreateModelRenderer());

		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		m_Manager->SetTextureLoader(m_Renderer->CreateTextureLoader());
		m_Manager->SetModelLoader(m_Renderer->CreateModelLoader());
		m_Manager->SetMaterialLoader(m_Renderer->CreateMaterialLoader());
		m_Manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
		// ���C���[��O�ʂɁi�v�C���j
		SetDrawLayer(1);
	}

	void  EfkInterface::OnUpdate() {
		// �G�t�F�N�g�̍X�V�������s��
		m_Manager->Update();
	}

	void EfkInterface::OnDraw() {
		// �r���[�Ǝˉe�s���ݒ�
		auto& camera = GetStage()->GetView()->GetTargetCamera();
		SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());

		// �G�t�F�N�g�̕`��J�n�������s���B
		m_Renderer->BeginRendering();

		// �G�t�F�N�g�̕`����s���B
		m_Manager->Draw();

		// �G�t�F�N�g�̕`��I���������s���B
		m_Renderer->EndRendering();
	}

	void Mat4x4ToMatrix44(const bsm::Mat4x4& src, Effekseer::Matrix44& dest) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				dest.Values[i][j] = src(i, j);
			}
		}
	}

	void EfkInterface::SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj) {
		Effekseer::Matrix44 v, p;
		Mat4x4ToMatrix44(view, v);
		Mat4x4ToMatrix44(proj, p);
		m_Renderer->SetCameraMatrix(v);
		m_Renderer->SetProjectionMatrix(p);
	}
}
// end basecross