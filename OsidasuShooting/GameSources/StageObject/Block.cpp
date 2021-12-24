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
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;

		AdvancedMeshUtil::CreateCube(3.0f, m_transformData.Scale, vertices, indices);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"Block");
		drawComp->SetOwnShadowActive(true);
		drawComp->SetSamplerState(SamplerState::LinearWrap);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_CUBE");
	}

	// オブジェクトビルダー用のコンストラクタ
	Bumper::Bumper(const shared_ptr<Stage>& stage, const wstring& line)
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

	void Bumper::OnCreate() {
		// 描画コンポーネントの追加
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMeshResource(L"Bumper");
		drawComp->SetOwnShadowActive(true);
		drawComp->SetDiffuse(Col4(1, 0, 0, 1));

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		//collComp->SetDrawActive(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"Bumper");
	}
}