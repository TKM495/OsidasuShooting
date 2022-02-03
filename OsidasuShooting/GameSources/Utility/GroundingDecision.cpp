/*!
@file   GroundingDecision.cpp
@brief  �ڒn����N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �������l�̎���
	float GroundingDecision::m_threshold = 0.1f;

	GroundingDecision::GroundingDecision()
		:m_height(0.0f), m_isInit(false)
	{}

	GroundingDecision::GroundingDecision(float height)
		: m_height(height), m_isInit(true)
	{}

	GroundingDecision::GroundingDecision(const Vec3& scale)
		: m_height(scale.y), m_isInit(true)
	{}

	bool GroundingDecision::Calculate(const Vec3& pos) {
		if (!m_isInit) {
			throw BaseException(
				L"����������Ă��܂���B",
				L"if (!m_isInit)",
				L"GroundingDecision::Calculate()"
			);
		}
		// �X�e�[�W��̂��ׂẴQ�[���I�u�W�F�N�g���擾
		auto objs = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetGameObjectVec();
		for (auto obj : objs) {
			// CollisionObb�R���|�[�l���g������ꍇ
			auto ColObb = obj->GetComponent<CollisionObb>(false);
			if (ColObb) {
				bool hasTag = false;
				for (auto tag : m_tagDoNotDecision) {
					if (obj->FindTag(tag)) {
						hasTag = true;
						break;
					}
				}

				if (hasTag || !obj->IsDrawActive())
					continue;

				auto Obb = ColObb->GetObb();
				// OBB�Ɛ����̏Փ˔���
				if (HitTest::SEGMENT_OBB(pos,
					pos + Vec3(0.0f, -((m_height / 2.0f) + m_threshold), 0.0f), Obb))
				{
					return true;
				}
			}
		}
		return false;
	}
}