#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UIEffect::OnCreate() {
		m_textureSize = Utility::GetTextureSize(m_textureKey);
		// 1つあたりのサイズを求める
		Vec2 pieceSize(
			m_textureSize.x / m_divisionCount.x,
			m_textureSize.y / m_divisionCount.y
		);

		pieceSize /= 2.0f;

		Col4 color(1.0f);
		// 頂点のデータ (番号は左上から右下まで)
		vertices = {
			{Vec3(-pieceSize.x,+pieceSize.y,0.0f),color,Vec2(0,0)}, //0
			{Vec3(+pieceSize.x,+pieceSize.y,0.0f),color,Vec2(1,0)}, //1

			{Vec3(-pieceSize.x,-pieceSize.y,0.0f),color,Vec2(0,1)}, //2
			{Vec3(+pieceSize.x,-pieceSize.y,0.0f),color,Vec2(1,1)},  //3
		};
		// 頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, // 上の三角形
			2, 1, 3  // 下の三角形
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);

		SetAlphaActive(true);
		m_timer.SetIntervalTime(m_maxIndex / (float)m_frameRate);
	}

	void UIEffect::OnUpdate() {
		m_timer.Count();

		//Debug::GetInstance()->Log(m_timer.GetElaspedTime());
		m_pieceIndex = int(m_timer.GetElaspedTime() / m_displayTime);
		if (m_pieceIndex >= m_maxIndex) {
			m_pieceIndex = 0;
			m_timer.Reset();
		}
		Debug::GetInstance()->Log(m_pieceIndex);
		vector<VertexPositionColorTexture> newVertices;
		uint32_t pieceX = m_pieceIndex % (int)m_divisionCount.x;
		uint32_t pieceY = m_pieceIndex / m_divisionCount.x;
		float pieceWidth = 1.0f / (float)m_divisionCount.x;
		float pieceHeight = 1.0f / (float)m_divisionCount.y;

		float pieceStartX = (float)pieceX * pieceWidth;
		float pieceEndX = pieceStartX + pieceWidth;

		float pieceStartY = (float)pieceY * pieceHeight;
		float pieceEndY = pieceStartY + pieceHeight;

		for (size_t i = 0; i < vertices.size(); i++) {
			Vec2 uv = vertices[i].textureCoordinate;
			switch (i) {
			case 0:
				uv.x = pieceStartX;
				uv.y = pieceStartY;
				break;
			case 1:
				uv.x = pieceEndX;
				uv.y = pieceStartY;
				break;
			case 2:
				uv.x = pieceStartX;
				uv.y = pieceEndY;
				break;
			case 3:
				uv.x = pieceEndX;
				uv.y = pieceEndY;
				break;
			}
			auto v = VertexPositionColorTexture(
				vertices[i].position,
				vertices[i].color,
				uv
			);
			newVertices.push_back(v);
		}
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}
}