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
		:m_radius(0.0f), m_isInit(false)
	{}

	GroundingDecision::GroundingDecision(float radius)
		: m_radius(radius), m_isInit(true)
	{}

	GroundingDecision::GroundingDecision(const Vec3& scale)
		: m_isInit(true)
	{
		m_radius = scale.y / 2.0f;
	}

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
				auto Obb = ColObb->GetObb();
				// OBB�Ɛ����̏Փ˔���
				if (HitTest::SEGMENT_OBB(pos,
					pos + Vec3(0.0f, -(m_radius + m_threshold), 0.0f), Obb))
				{
					return true;
				}
			}
		}
		return false;
	}
}