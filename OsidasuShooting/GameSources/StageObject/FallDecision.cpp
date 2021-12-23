/*!
@file   FallDecision.cpp
@brief  触れたら落下判定とするオブジェクトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FallDecision::FallDecision(const shared_ptr<Stage>& stage)
		:AdvancedGameObject(stage) {
		m_transformData.Position = Vec3(0, -20, 0);
		m_transformData.Scale = Vec3(200, 1, 200);
	}

	FallDecision::FallDecision(const shared_ptr<Stage>& stage, const wstring& line)
		: AdvancedGameObject(stage)
	{
		auto tokens = DataExtracter::DelimitData(line);
		m_transformData = DataExtracter::TransformDataExtraction(tokens);
		Debug::GetInstance()->Log(m_transformData.Scale);
	}

	void FallDecision::OnCreate() {
		auto collComp = AddComponent<CollisionObb>();
		collComp->AddExcludeCollisionTag(L"FallDecision");
		collComp->SetAfterCollision(AfterCollision::None);
		collComp->SetDrawActive(true);
		AddTag(L"FallDecision");
	}

	void FallDecision::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto ptr = dynamic_pointer_cast<PlayerBase>(other);
		if (ptr) {
			ptr->Respawn();
		}
		else {
			GetStage()->RemoveGameObject<GameObject>(other);
		}
	}
}