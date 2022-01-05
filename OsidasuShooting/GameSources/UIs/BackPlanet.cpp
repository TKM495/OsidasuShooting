/*!
@file   BackPlanet.cpp
@brief  �w�i�̉F���̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BackPlanet::OnCreate() {
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// �e�N�X�`�����W��UV���`
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		auto halfSize = size / 2.0f;
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

		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();
		pos.y -= 700;
		ptrTrans->SetPosition(pos);

		auto scl = ptrTrans->GetScale();
		scl *= 1.5f;
		ptrTrans->SetScale(scl);
	}

	void BackPlanet::OnUpdate() {

		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();
		pos.y += 0.005f;
		ptrTrans->SetPosition(pos);
	}
}