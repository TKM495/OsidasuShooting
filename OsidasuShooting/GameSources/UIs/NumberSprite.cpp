/*!
@file NumberSprite.cpp
@brief �����̃X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Number::OnCreate()
	{
		//texture 640 x 128
		float sideSize = 640.0f;
		float fSidSize = 1024.0f;
		float higthSize = -128.0f;
		float fontSize = 64.0f;
		float zeroSize = 0.0f;
		float oneSize = 1.0f;
		float quatSize = 0.25f;
		float helfSize = 0.5f;
		float tqatSize = 0.75f;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		// �|���S���̒��_�f�[�^
		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(zeroSize,  zeroSize, zeroSize),color,Vec2(zeroSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(sideSize,  zeroSize, zeroSize),color,Vec2(sideSize / fSidSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(zeroSize, higthSize, zeroSize),color,Vec2(zeroSize,  oneSize))},
			{VertexPositionColorTexture(Vec3(sideSize, higthSize, zeroSize),color,Vec2(sideSize / fSidSize,  oneSize))}
		};

		// ���_�C���f�b�N�X
		vector<uint16_t> indeces = {
			0, 1, 2,
			1, 3, 2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indeces);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey); // TitleStage���Őݒ�

		SetAlphaActive(true);

		// �ʒu�A�g��k��
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos(-sideSize * helfSize * tqatSize, -higthSize * tqatSize * tqatSize, zeroSize);
		Vec3 scl(oneSize, oneSize, oneSize);
		ptrTrans->SetPosition(pos);
		ptrTrans->SetScale(scl);

	};
}