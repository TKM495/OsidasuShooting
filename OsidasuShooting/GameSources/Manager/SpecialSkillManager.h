#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class SpecialSkillManager :public BaseSingleton<SpecialSkillManager> {
	private: //�V���O���g���֌W
		SpecialSkillManager();
		~SpecialSkillManager() {}
		friend class BaseSingleton<SpecialSkillManager>;
	private:
		// �K�E�Z���N������
		bool m_isActive;
		shared_ptr<SpecialSkill> m_specialSkill;
	public:
		// �����ł��邩
		bool IsInvocable() {
			return !m_isActive;
		}

		/**
		 * @brief �K�E�Z�̋N��
		 *
		 * @param type �^�C�v
		 * @return ����������true
		 */
		bool ActiveSpecialSkill(PlayerType type, const shared_ptr<PlayerBase>& owner);

		// �I��������
		bool IsEnded();
	};
}
