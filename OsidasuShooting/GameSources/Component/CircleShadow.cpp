#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CircleShadow::CircleShadow(const shared_ptr<GameObject>& gameObjectPtr)
		:Component(gameObjectPtr)
	{}

	void CircleShadow::OnCreate() {
		m_shadow = ObjectFactory::Create<BoardPoly>(
			GetStage(), L"CircleShadow", TransformData(Vec3(0), Vec3(2)));
	}

	void CircleShadow::OnUpdate() {
		auto pos = GetGameObject()->GetComponent<Transform>()->GetPosition();
		// ステージ上のすべてのゲームオブジェクトを取得
		auto objs = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetGameObjectVec();
		auto shadowPos = pos + Vec3(0, -100, 0);
		for (auto obj : objs) {
			if (obj->FindTag(L"FallDecision"))
				continue;

			// CollisionObbコンポーネントがある場合
			auto ColObb = obj->GetComponent<CollisionObb>(false);

			if (ColObb) {
				auto Obb = ColObb->GetObb();
				// OBBと線分の衝突判定
				if (HitTest::SEGMENT_OBB(pos, pos + Vec3(0, -10, 0), Obb))
				{
					shadowPos.y = Obb.m_Center.y + Obb.m_Size.y + 0.01f;
					break;
				}
			}
		}
		m_shadow->GetTransform()->SetPosition(shadowPos);
	}

	void CircleShadow::OnDraw() {
		m_shadow->OnDraw();
	}
}