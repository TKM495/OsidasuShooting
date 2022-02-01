#pragma once
#include "stdafx.h"

namespace basecross {
	using Func = function<void(void)>;
	class OnceTriggerObject :public GameObject {
	public:
		OnceTriggerObject(const shared_ptr<Stage>& stage)
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

		/**
		 * @brief �֐��̃��Z�b�g
		 *
		 * @param key �L�[
		 */
		void ResetFunction(const wstring& key);
	};

	class OnceTrigger :public Component {
		struct FuncData {
			Func Function;
			bool bOnce;
		};
		// �L�[�ƃf�[�^��map
		map<wstring, FuncData> m_funcMap;
	public:
		OnceTrigger(const shared_ptr<GameObject>& gameObjectPtr)
			:Component(gameObjectPtr)
		{}

		void OnCreate()override {}
		void OnUpdate()override {}
		void OnDraw()override {}

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

		/**
		 * @brief �֐��̃��Z�b�g
		 *
		 * @param key �L�[
		 */
		void ResetFunction(const wstring& key);
	};
}
