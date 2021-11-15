/*!
@file BattlePlayersUIs.cpp
@brief ÉvÉåÉCÉÑÅ[èÓïÒé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BattlePlayersUIs::OnCreate()
	{
		//texture 2048 x 256
		float sideSize = 2048.0f;
		float highSize = -256.0f;
		float iconSize = 256.0f;
		float zeroSize = 0.0f;
		float oneSize = 1.0f;
		float quatSize = 0.25f;
		float helfSize = 0.5f;
		float tqatSize = 0.75f;
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(zeroSize,zeroSize,zeroSize),color,Vec2())},
			{VertexPositionColorTexture(Vec3(iconSize,zeroSize,zeroSize),color,Vec2())},
			{VertexPositionColorTexture(Vec3(zeroSize,highSize,zeroSize),color,Vec2())},
			{VertexPositionColorTexture(Vec3(iconSize,highSize,zeroSize),color,Vec2())}
		};
	}
}
