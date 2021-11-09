#include "stdafx.h"
#include "Project.h"

namespace basecross {
	bool GroundingDecision::Calculate(const Vec3& pos) {
		auto objs = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetGameObjectVec();
		for (auto obj : objs) {
			auto ColObb = obj->GetComponent<CollisionObb>(false);
			if (ColObb) {
				auto Obb = ColObb->GetObb();
				if (HitTest::SEGMENT_OBB(pos, pos + Vec3(0.0f, -1.0f, 0.0f), Obb)) {
					return true;
				}
			}
		}
		return false;
	}
}