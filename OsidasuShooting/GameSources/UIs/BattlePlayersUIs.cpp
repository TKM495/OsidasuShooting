/*!
@file BattlePlayersUIs.cpp
@brief プレイヤー情報実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BattlePlayersUIs::PlayersNumberUICreate() {
		//texture 2048 x 256
		float fSidSize = 2048.0f; //fullSideSize、全体の横の長さ
		float highSize = -256.0f;
		float iconSize = 256.0f;
		float zeroSize = 0.0f;
		float  oneSize = 1.0f;
		float quatSize = 0.25f;
		float helfSize = 0.5f;
		float tqatSize = 0.75f;

		// Col4 color1P(0.0f, 0.0f, 0.8f, 1.0f);
		// Col4 color2P(1.0f, 0.0f, 0.0f, 1.0f);
		// Col4 color3P(1.0f, 1.0f, 0.0f, 1.0f);
		// Col4 color4P(0.0f, 0.8f, 0.0f, 1.0f);
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		float setNumber = static_cast<float>(m_number);

		vertices = {
			{VertexPositionColorTexture(Vec3(zeroSize,zeroSize,zeroSize),color,Vec2((setNumber + zeroSize) * iconSize / fSidSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(iconSize,zeroSize,zeroSize),color,Vec2((setNumber +  oneSize) * iconSize / fSidSize, zeroSize))},
			{VertexPositionColorTexture(Vec3(zeroSize,highSize,zeroSize),color,Vec2((setNumber + zeroSize) * iconSize / fSidSize,  oneSize))},
			{VertexPositionColorTexture(Vec3(iconSize,highSize,zeroSize),color,Vec2((setNumber +  oneSize) * iconSize / fSidSize,  oneSize))}
		};

		vector<uint16_t> indices = {
			0,1,2,
			1,3,2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
		SetAlphaActive(true);

		PlayersIconUICreate(m_iconNumber);
	}


	void BattlePlayersUIs::PlayersIconUICreate(int value) {
		// 画像の順番がめんどくさいことになったのでここで扱いやすくする
		auto pNum = value;
		if(pNum == 0) { // PlayerNumCirecle
			pNum = 0;
			m_objIconSize = 0.55f;
		}
		else if (pNum >= 1 && pNum <= 4) {	// Player1~4P
			pNum += 3;
			m_objIconSize = 0.5f;
		}
		else if(pNum == 5) {			// CPUPlayer
			pNum = 3;
			m_objIconSize = 0.5f;
		}
		else if (pNum == 6) { // Crown
			pNum = 2;
			m_objIconSize = 0.43f;
		}
		SetPlayerNumValue(pNum);
	}

	void BattlePlayersUIs::SetPlayerNumValue(int value) {
		m_number = value;
		float fSidSize = 2048.0f; //fullSideSize、全体の横の長さ
		float highSize = -256.0f;
		float iconSize = 256.0f;
		float zeroSize = 0.0f;
		float oneSize = 1.0f;
		float setNumber = static_cast<float>(m_number);

		vertices[0].textureCoordinate = Vec2((setNumber + zeroSize) * iconSize / fSidSize, zeroSize);
		vertices[1].textureCoordinate = Vec2((setNumber + oneSize) * iconSize / fSidSize, zeroSize);
		vertices[2].textureCoordinate = Vec2((setNumber + zeroSize) * iconSize / fSidSize, oneSize);
		vertices[3].textureCoordinate = Vec2((setNumber + oneSize) * iconSize / fSidSize, oneSize);

		auto ptrTrans = GetComponent<Transform>();
		auto setSenter = iconSize * 0.35f;
		ptrTrans->SetScale(Vec3(m_objIconSize));
		ptrTrans->SetPosition(Vec3(-setSenter, setSenter,0));
		//ptrTrans->SetPosition(Vec3(0, 0,0));

		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->UpdateVertices(vertices);

	}

	void BattlePlayersUIs::OnCreate()
	{
		PlayersNumberUICreate();
	}


	void BombIcon::OnCreate() {
		auto texture = L"BomberUI";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(0.4f);
		BaseSprite::SettingPosition(m_setPos);
	}
}
