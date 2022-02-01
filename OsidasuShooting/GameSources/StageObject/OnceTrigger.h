#pragma once
#include "stdafx.h"

namespace basecross {
	class OnceTrigger :public GameObject {
		using Func = function<void(void)>;
		struct FuncData {
			Func Function;
			bool bOnce;
		};
		// �L�[�ƃf�[�^��map
		map<wstring, FuncData> m_funcMap;
	public:
		OnceTrigger(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		/**
		 * @brief �֐����Z�b�g
		 *
		 * @param key �L�[
		 * @param func �֐��̃|�C���^
		 */
		void SetFunction(const wstring& key, Func func);

		/**
		 * @brief �֐������s
		 *
		 * @param key ���s����֐��̃L�[
		 */
		void LaunchFunction(const wstring& key);
	};
}
