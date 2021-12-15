#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class SpecialSkillManager :public BaseSingleton<SpecialSkillManager> {
	private: //シングルトン関係
		SpecialSkillManager();
		~SpecialSkillManager() {}
		friend class BaseSingleton<SpecialSkillManager>;
	private:
		// 必殺技が起動中か
		bool m_isActive;
		shared_ptr<SpecialSkill> m_specialSkill;
	public:
		// 発動できるか
		bool IsInvocable() {
			return !m_isActive;
		}

		/**
		 * @brief 必殺技の起動
		 *
		 * @param type タイプ
		 * @return 成功したらtrue
		 */
		bool ActiveSpecialSkill(PlayerType type, const shared_ptr<PlayerBase>& owner);

		// 終了したか
		bool IsEnded();
	};
}
