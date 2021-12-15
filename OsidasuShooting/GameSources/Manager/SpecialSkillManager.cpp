#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// ������
	unique_ptr<SpecialSkillManager, SpecialSkillManager::Deleter> SpecialSkillManager::m_instance = nullptr;

	SpecialSkillManager::SpecialSkillManager()
		:m_isActive(false)
	{}

	bool SpecialSkillManager::ActiveSpecialSkill(PlayerType type, const shared_ptr<PlayerBase>& owner) {
		// ���łɒN�����K�E�Z���N�����̏ꍇ
		if (m_isActive)
			return false;
		switch (type)
		{
		case PlayerType::Laser:
			m_specialSkill = owner->InstantiateGameObject<SpecialLaser>(
				owner, owner->GetTransform()->GetPosition(), owner->GetDirectionToFace());
			break;
			//case PlayerType::Missile:
			//	break;
		default:
			return false;
		}
		m_isActive = true;
		return m_isActive;
	}

	bool SpecialSkillManager::IsEnded() {
		// �N�����̂��̂��Ȃ��ꍇ or �|�C���^���L���łȂ��ꍇ
		if (!m_isActive || !m_specialSkill)
			return true;

		if (m_specialSkill->IsEnded()) {
			m_specialSkill->Destroy<SpecialSkill>();
			m_isActive = false;
			return true;
		}

		return m_specialSkill->IsEnded();
	}
}