/*!
@file   BreakBlock.cpp
@brief	壊れるブロッククラスの実態
*/

#include "stdafx.h"
#include "Project.h"
#include "Bullet.h"

namespace basecross {
	BreakBlock::BreakBlock(
		const shared_ptr<Stage>& stage,
		const wstring& line
	) :
		AdvancedGameObject(stage)
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
		//m_hp = (float)_wtof(tokens[14].c_str()); // HP
		//m_wakeupTime = (float)_wtof(tokens[15].c_str()); // 復活時間
		m_hp = 5;
		m_wakeupTime = 3;
	}

	void BreakBlock::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;

		AdvancedMeshUtil::CreateCube(3.0f, m_transformData.Scale, vertices, indices);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"BreakBlock");
		drawComp->SetOwnShadowActive(true);
		drawComp->SetSamplerState(SamplerState::LinearWrap);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(L"DEFAULT_CUBE");

		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);
		//// ブロックとの当たり判定を無視
		//ptrColl->AddExcludeCollisionTag(L"Block");
		//ptrColl->SetFixed(true);

		//// 本来の一個下に設置
		//m_setPosition = GetTransform()->GetPosition();
		//auto setPos = m_setPosition;
		//setPos.y = -1;
		//GetTransform()->SetPosition(setPos);
		//ApplyTransform();

		m_nowHp = m_hp;

		AddTag(L"Break");
	}

	void BreakBlock::OnUpdate() {
		if (!m_isSetUp) {
			//	SetUpAnimation();
		}
		else {
			auto findBlock = GetDrawActive();
			auto ptrColl = GetComponent<CollisionObb>();
			if (findBlock) ptrColl->SetUpdateActive(true);
			else {
				const auto& app = App::GetApp();
				const auto delta = app->GetElapsedTime();
				ptrColl->SetUpdateActive(false);
				if (m_wakeupTime >= m_nowTime) {
					m_nowTime += delta;
				}
				else {
					SetDrawActive(true);
					m_nowHp = m_hp;
					m_nowTime = 0;
				}
			}
		}

		m_isSetUp = true;
	}

	void BreakBlock::SetUpAnimation() {
		//auto pos = GetTransform()->GetPosition();
		//if (pos.y < m_setPosition.y) {
		//	pos.y = m_setPosition.y;

		//	m_isSetUp = true;
		//}
		//else {
		//	if (pos.y > m_setPosition.y - 0.5f) {
		//		pos = m_setPosition;
		//	}
		//	else {
		//		auto movePosY = (m_setPosition.y - pos.y) * 0.5f;
		//		pos.y = movePosY;
		//	}
		//}
		//GetTransform()->SetPosition(pos);
	}

	void BreakBlock::BlockDamage(float damage) {
		if (m_nowHp >= 0) {
			m_nowHp -= damage;
		}
		else {
			SetDrawActive(false);
		}
	}
}