#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CircleShadow::CircleShadow(const shared_ptr<GameObject>& gameObjectPtr,
		float scale)
		:Component(gameObjectPtr), m_scale(scale)
	{}
	CircleShadow::CircleShadow(const shared_ptr<GameObject>& gameObjectPtr)
		: CircleShadow(gameObjectPtr, 1.0f)
	{}

	void CircleShadow::OnCreate() {
		m_shadow = ObjectFactory::Create<BoardPoly>(
			GetStage(), L"CircleShadow", TransformData(Vec3(0), Vec3(m_scale)));
		m_shadow->GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1, 1, 1, 0.75f));
	}

	void CircleShadow::OnUpdate() {
		auto pos = GetGameObject()->GetComponent<Transform>()->GetPosition();
		// �X�e�[�W��̂��ׂẴQ�[���I�u�W�F�N�g���擾
		auto objs = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetGameObjectVec();
		auto shadowPos = pos + Vec3(0, -100, 0);
		for (auto obj : objs) {
			if (obj->FindTag(L"FallDecision"))
				continue;

			// CollisionObb�R���|�[�l���g������ꍇ
			auto ColObb = obj->GetComponent<CollisionObb>(false);

			if (ColObb) {
				auto Obb = ColObb->GetObb();
				// OBB�Ɛ����̏Փ˔���
				if (HitTest::SEGMENT_OBB(pos, pos + Vec3(0, -100, 0), Obb))
				{
					shadowPos.y = Obb.m_Center.y + Obb.m_Size.y + 0.01f;
					break;
				}
			}
		}
		m_shadow->GetTransform()->SetPosition(shadowPos);
	}

	void CircleShadow::OnDraw() {
		if (GetGameObject()->GetDrawActive())
			m_shadow->OnDraw();
	}
}