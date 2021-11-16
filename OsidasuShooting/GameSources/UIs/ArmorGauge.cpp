#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ArmorGauge::OnCreate() {
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(L"Gauge");
		//size *= 0.5f;
		// �e�N�X�`�����W��UV���`
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		// �e�N�X�`�����W����UV���W�ɕϊ�
		Utility::ConvertToUVCoordinates(uv, L"Gauge", uvs);
		Col4 color(1.0f);
		// ���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-size.x,+size.y,0.0f),color,uvs[0]}, //0
			{Vec3(+size.x,+size.y,0.0f),color,uvs[1]}, //1

			{Vec3(-size.x,-size.y,0.0f),color,uvs[2]}, //2
			{Vec3(+size.x,-size.y,0.0f),color,uvs[3]},  //3
		};
		// ���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2, // ��̎O�p�`
			2, 1, 3  // ���̎O�p�`
		};

		auto ptrDraw = AddComponent<PCTGaugeSprite>(vertices, indices);
		ptrDraw->SetTextureResource(L"Gauge");
		SetAlphaActive(true);
	}
	void ArmorGauge::OnUpdate() {
		//if (m_testTimer.Count())
		//	m_testTimer.Reset();
		auto ptrDraw = GetComponent<PCTGaugeSprite>();
		ptrDraw->SetRate(m_player->GetArmorPointRate());
	}
}