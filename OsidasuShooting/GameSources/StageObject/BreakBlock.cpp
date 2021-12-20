/*!
@file   BreakBlock.cpp
@brief	リフレクターブロッククラスの実態
*/

#include "stdafx.h"
#include "Project.h"
#include "Bullet.h"

namespace basecross {
	BreakBlock::BreakBlock(
		const shared_ptr<Stage>& stage,
		const TransformData transformData,
		const wstring& line
	) :
		Block(stage, transformData)
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

	void BreakBlock::OnCreate() {
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		// ブロックとの当たり判定を無視
		ptrColl->AddExcludeCollisionTag(L"Block");
		ptrColl->SetFixed(true);

		// 本来の一個下に設置
		m_setPosition = GetTransform()->GetPosition();
		auto setPos = m_setPosition;
		setPos.y = -1;
		GetTransform()->SetPosition(setPos);
		ApplyTransform();

		AddTag(L"Break");
	}

	void BreakBlock::OnUpdate() {
		if (!m_isSetUp) {
		//	SetUpAnimation();
		}
		else {
			auto ptrColl = GetComponent<CollisionObb>();
			ptrColl->SetAfterCollision(AfterCollision::Auto);
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

	void BreakBlock::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Bullet") || other->FindTag(L"Player")) {
			this->SetDrawActive(false);
			this->SetUpdateActive(false);
		}
	}

}