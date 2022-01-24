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

		AdvancedMeshUtil::CreateCube(2.0f, m_transformData.Scale, vertices, indices);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"Block");
		drawComp->SetOwnShadowActive(true);
		drawComp->SetSamplerState(SamplerState::LinearWrap);

		auto collComp = AddComponent<CollisionObb>();
		collComp->AddExcludeCollisionTag(L"Block");
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
		auto key = L"Bumper";
		// 描画コンポーネントの追加
		auto drawComp = AddComponent<PNTBoneModelDraw>();
		drawComp->SetMultiMeshResource(key);
		//drawComp->SetOwnShadowActive(true);

		auto data = CSVLoad::GetInstance()->GetData(L"ModelAnimationData");

		for (auto line : data) {
			auto c = DataExtracter::DelimitData(line);
			if (c[0] == key) {
				auto name = c[1];
				auto start = (int)_wtof(c[2].c_str());
				auto end = (int)_wtof(c[3].c_str());
				auto loop = c[4] == L"TRUE";
				drawComp->AddAnimation(name, start, end - start, loop);
			}
		}

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		//collComp->SetDrawActive(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMultiMeshResource(key);
	}

	void Bumper::OnUpdate() {
		if (!m_isAnimation)
			return;

		auto delta = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(delta);
		if (drawComp->IsTargetAnimeEnd()) {
			m_isAnimation = false;
		}
	}

	void Bumper::PlayAnimation() {
		m_isAnimation = true;
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Move");
	}
}