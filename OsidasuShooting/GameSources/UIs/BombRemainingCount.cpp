#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BombRemainingCount::OnCreate() {
		// x,y,z‚·‚×‚Ä“¯‚¶’l‚Æ‰¼’è
		auto scale = m_transformData.Scale.x;

		auto addOffset = Vec3(70.0f, 0, 0) * scale;     // ˆê•¶Žš‚Ì‘å‚«‚³
		Vec3 basePos = -(addOffset / 2);

		m_numbers.resize(2);
		for (auto& number : m_numbers) {
			number = ObjectFactory::Create<Number>(GetStage(), 0);
			auto trans = number->GetComponent<Transform>();
			trans->SetPosition(m_transformData.Position + basePos);
			trans->SetScale(m_transformData.Scale);
			trans->SetRotation(m_transformData.Rotation);
			trans->SetParent(GetThis<BombRemainingCount>());

			basePos += addOffset;
		}
		ApplyTransform();
	}

	void BombRemainingCount::OnUpdate() {
		int count = m_player->GetBombCount();
		int place = static_cast<int>(pow(10, m_numbers.size() - 1));
		for (auto& number : m_numbers) {
			int num = count / place % 10;
			number->SetValue(num);
			place /= 10;
			if (count > 0) {
				number->SetColor(Col4(1));
			}
			else {
				number->SetColor(Col4(1, 0, 0, 1));
			}
		}
	}

	void BombRemainingCount::OnDraw() {
		for (auto number : m_numbers) {
			number->OnDraw();
		}
	}
}