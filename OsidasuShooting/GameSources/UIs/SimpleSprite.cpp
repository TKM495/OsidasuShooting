#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SimpleSprite::OnCreate() {
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// �e�N�X�`�����W��UV���`
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		halfSize = size / 2.0f;
		// �e�N�X�`�����W����UV���W�ɕϊ�
		Utility::ConvertToUVCoordinates(uv, m_textureKey, uvs);
		Col4 color(1.0f);
		// ���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfSize.x,+halfSize.y,0.0f),color,uvs[0]}, //0
			{Vec3(+halfSize.x,+halfSize.y,0.0f),color,uvs[1]}, //1

			{Vec3(-halfSize.x,-halfSize.y,0.0f),color,uvs[2]}, //2
			{Vec3(+halfSize.x,-halfSize.y,0.0f),color,uvs[3]},  //3
		};
		// ���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2, // ��̎O�p�`
			2, 1, 3  // ���̎O�p�`
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_textureKey);
		// �e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); // �������T�|�[�g����&���ʕ`��ɂȂ�
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
		// ���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionNormalTexture> vertices = {
			{Vec3(-halfSize.x,0.0f,+halfSize.y),normal,Vec2(0,0)}, //0
			{Vec3(+halfSize.x,0.0f,+halfSize.y),normal,Vec2(1,0)}, //1

			{Vec3(-halfSize.x,0.0f,-halfSize.y),normal,Vec2(0,1)}, //2
			{Vec3(+halfSize.x,0.0f,-halfSize.y),normal,Vec2(1,1)},  //3
		};
		// ���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2, // ��̎O�p�`
			2, 1, 3  // ���̎O�p�`
		};

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetTextureResource(m_textureKey);

		SetAlphaActive(true); // �������T�|�[�g����&���ʕ`��ɂȂ�
		SetUpdateActive(false);
	}
}