/*!
@file NumberSprite.h
@brief 数字のスプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class Number : public AdvancedGameObject {
		//bool m_trace;
		//Vec2 m_startScale;
		//Vec2 m_startPos;
		//wstring m_textureKey;
		int m_number;
		vector<VertexPositionColorTexture> vertices;

	public:
		Number(const shared_ptr<Stage>& stage, //const wstring& TextureKey,
			 //bool Trace,const Vec2& StartScale, const Vec2& StartPos,
			int number) :
			AdvancedGameObject(stage),
			//m_textureKey(TextureKey),
			//m_trace(Trace),
			//m_startScale(StartScale),
			//m_startPos(StartPos),
			m_number(number)
		{}

		virtual ~Number() {};

		void SetValue(int value) {
			m_number = value;
			float sideSize = 640.0f;
			float fSidSize = 1024.0f; //fullSideSize、全体の横の長さ
			float highSize = 128.0f;
			float fontSize = 64.0f;
			float zeroSize = 0.0f;
			float  oneSize = 1.0f;

			float setNumber = static_cast<float>(m_number);

			vertices[0].textureCoordinate = Vec2((setNumber + zeroSize) * fontSize / fSidSize, zeroSize);
			vertices[1].textureCoordinate = Vec2((setNumber + oneSize) * fontSize / fSidSize, zeroSize);
			vertices[2].textureCoordinate = Vec2((setNumber + zeroSize) * fontSize / fSidSize, oneSize);
			vertices[3].textureCoordinate = Vec2((setNumber + oneSize) * fontSize / fSidSize, oneSize);

			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(vertices);
		}


		void SetAlpha(float alpha)
		{
			for (int i = 0; i < vertices.size() - 1; i++)
			{
				vertices[i].color.w = alpha;
			}
			auto drawComp = GetComponent<PCTSpriteDraw>();
			auto color = drawComp->GetDiffuse();
			color.w = alpha;
			drawComp->SetDiffuse(color);
		}
		
		void SetColor(Col4 color)
		{
			for (int i = 0; i < vertices.size() - 1; i++)
			{
				vertices[i].color = color;
			}
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(color);
		}

		void OnCreate() override;
		void OnUpdate() {};
	};
}