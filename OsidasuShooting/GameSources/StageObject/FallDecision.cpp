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
	}

	void FallDecision::OnCreate() {
		auto collComp = AddComponent<CollisionObb>();
		collComp->AddExcludeCollisionTag(L"FallDecision");
		collComp->SetAfterCollision(AfterCollision::None);
		collComp->SetDrawActive(true);
		AddTag(L"FallDecision");

		auto myRot = GetTransform()->GetRotation();
		auto efkComp = AddComponent<EfkComponent>();
		// 落ちたときのエフェクトの代わり
		efkComp->SetEffectResource(L"Explosion",
			TransformData(
				Vec3(0.0f),
				Vec3(1.0f, 5.0f, 1.0f),
				Utility::ConvertRadVecToDegVec(myRot))
		);
	}

	void FallDecision::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto ptr = dynamic_pointer_cast<PlayerBase>(other);
		if (ptr) {
			auto pos = other->GetComponent<Transform>()->GetPosition();
			auto efkComp = GetComponent<EfkComponent>();
			efkComp->Play(L"Explosion");
			efkComp->SetPosition(L"Explosion", pos);

			ptr->Died();
		}
		else {
			GetStage()->RemoveGameObject<GameObject>(other);
		}
	}
}