#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LinePoint::OnCreate() {
		Col4 color(1.0f);
		// ���_�̃f�[�^
		vector<VertexPositionColor> vertices = {
			{Vec3(0.0f,1.0f,0.0f),color},
			{Vec3(1.0f,0.0f,0.0f),color},
			{Vec3(0.0f,0.0f,1.0f),color},
			{Vec3(-1.0f,0.0f,0.0f),color},
			{Vec3(0.0f,0.0f,-1.0f),color},
			{Vec3(0.0f,-1.0f,0.0f),color},
		};

		// ���_�C���f�b�N�X
		vector<uint16_t> indices = {
			// ��
			0,2,1,
			0,3,2,
			0,4,3,
			0,1,4,
			// ��
			5,1,2,
			5,2,3,
			5,3,4,
			5,4,1,
		};

		auto drawComp = AddComponent<PCStaticDraw>();
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
	}

	void LinePoint::SetColor(const Col4& color) {
		GetComponent<PCStaticDraw>()->SetDiffuse(color);
	}
}