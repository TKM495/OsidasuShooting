#pragma once
#include "stdafx.h"

namespace basecross {
	class MySpriteBaseDraw :public DrawComponent {
	private:
		// ���b�V��
		shared_ptr<MeshResource> m_spriteMesh;
		// �e�N�X�`�����\�[�X
		weak_ptr<TextureResource> m_textureResource;
		// �G�~�b�V�u�F
		Col4 m_emissive;
		// �f�t���[�Y�F
		Col4 m_diffuse;
	protected:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param gameObjectPtr �Q�[���I�u�W�F�N�g�̃|�C���^
		 */
		explicit MySpriteBaseDraw(const shared_ptr<GameObject>& gameObjectPtr);
		/**
		 * @brief �f�X�g���N�^
		 */
		virtual ~MySpriteBaseDraw();
	public:
		/**
		 * @brief ���_�ύX�ł���X�v���C�g���b�V�����쐬����i���łɂ���ꍇ�͍����ւ���j
		 *
		 * @param Vertices ���_�̔z��
		 * @param indices �C���f�b�N�X�̔z��
		 */
		template<typename T>
		void CreateMesh(vector<T>& Vertices, vector<uint16_t>& indices) {
			try {
				//���b�V���̍쐬�i�ύX�ł���j
				auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
				SetMeshResource(SpriteMesh);
			}
			catch (...) {
				throw;
			}
		}

		/**
		 * @brief ���_�o�b�t�@�̍X�V
		 *
		 * @param Vertices ���_�z��
		 */
		template<typename T>
		void UpdateVertices(const vector<T>& Vertices) {
			auto SpriteMesh = GetMeshResource();
			if (!SpriteMesh) {
				throw BaseException(
					L"���b�V�����쐬����Ă��܂���",
					L"if (!GetMeshResource())",
					L"SpriteBaseDraw::UpdateVertices()"
				);
			}
			if (Vertices.size() > SpriteMesh->GetNumVertices()) {
				throw BaseException(
					L"�X�V���钸�_���傫�����܂�",
					L"if (Vertices.size() > SpriteMesh->GetNumVertices())",
					L"SpriteBaseDraw::UpdateVertices()"
				);
			}
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();

			//���_�̕ύX
			//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
			D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
			D3D11_MAPPED_SUBRESOURCE mappedBuffer;
			//���_�̃}�b�v
			if (FAILED(pD3D11DeviceContext->Map(SpriteMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
				// Map���s
				throw BaseException(
					L"���_��Map�Ɏ��s���܂����B",
					L"if(FAILED(pID3D11DeviceContext->Map()))",
					L"SpriteBaseDraw::UpdateVertices()"
				);
			}
			//���_�̕ύX
			T* vertices
				= (T*)mappedBuffer.pData;
			for (size_t i = 0; i < SpriteMesh->GetNumVertices(); i++) {
				vertices[i] = Vertices[i];
			}
			//�A���}�b�v
			pD3D11DeviceContext->Unmap(SpriteMesh->GetVertexBuffer().Get(), 0);
		}

		/**
		 * @brief ���b�V�����\�[�X�̎擾
		 *
		 * @return ���b�V�����\�[�X
		 */
		shared_ptr<MeshResource> GetMeshResource() const;

		/**
		 * @brief ���b�V�����\�[�X�̐ݒ�
		 *
		 * @param MeshRes ���b�V�����\�[�X
		 */
		void SetMeshResource(const shared_ptr<MeshResource>& MeshRes);

		/**
		 * @brief �e�N�X�`�����\�[�X�̐ݒ�
		 *
		 * @param TextureRes �e�N�X�`�����\�[�X
		 */
		void SetTextureResource(const shared_ptr<TextureResource>& TextureRes);

		/**
		 * @brief �e�N�X�`�����\�[�X�̐ݒ�
		 *
		 * @param TextureKey �o�^����Ă���e�N�X�`���L�[
		 */
		void SetTextureResource(const wstring& TextureKey);

		/**
		 * @brief �e�N�X�`�����\�[�X�̎擾
		 *
		 * @return �e�N�X�`�����\�[�X
		 */
		shared_ptr<TextureResource> GetTextureResource() const;

		/**
		 * @brief �G�~�b�V�u�F�̎擾
		 *
		 * @return �G�~�b�V�u�F
		 */
		Col4 GetEmissive() const;

		/**
		 * @brief �G�~�b�V�u�F�̐ݒ�
		 *
		 * @param col �G�~�b�V�u�F
		 */
		void SetEmissive(const Col4& col);

		/**
		 * @brief �f�t���[�Y�F�̎擾
		 *
		 * @return �f�t���[�Y�F
		 */
		Col4 GetDiffuse() const;

		/**
		 * @brief �f�t���[�Y�F�̐ݒ�
		 *
		 * @param col �f�t���[�Y�F
		 */
		void SetDiffuse(const Col4& col);
	};
}