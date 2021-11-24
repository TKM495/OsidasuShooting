/*!
@file   Block.cpp
@brief  ブロッククラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Block::Block(const shared_ptr<Stage>& stage,
		const wstring& line)
		:AdvancedGameObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_transformData.Position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_transformData.Scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_transformData.Rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
	}

	void Block::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.5f));
		drawComp->SetTextureResource(L"Wall");
		drawComp->SetOwnShadowActive(true);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_CUBE");
	}

	void Block::OnUpdate() {
	}
}