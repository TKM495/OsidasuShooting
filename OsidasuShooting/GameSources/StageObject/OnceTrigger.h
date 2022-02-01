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
		 * @brief 関数をセット
		 *
		 * @param key キー
		 * @param func 関数のポインタ
		 */
		void SetFunction(const wstring& key, Func func);

		/**
		 * @brief 関数を実行
		 *
		 * @param key 実行する関数のキー
		 */
		void LaunchFunction(const wstring& key);

		/**
		 * @brief 関数のリセット
		 *
		 * @param key キー
		 */
		void ResetFunction(const wstring& key);
	};

	class OnceTrigger :public Component {
		struct FuncData {
			Func Function;
			bool bOnce;
		};
		// キーとデータのmap
		map<wstring, FuncData> m_funcMap;
	public:
		OnceTrigger(const shared_ptr<GameObject>& gameObjectPtr)
			:Component(gameObjectPtr)
		{}

		void OnCreate()override {}
		void OnUpdate()override {}
		void OnDraw()override {}

		/**
		 * @brief 関数をセット
		 *
		 * @param key キー
		 * @param func 関数のポインタ
		 */
		void SetFunction(const wstring& key, Func func);

		/**
		 * @brief 関数を実行
		 *
		 * @param key 実行する関数のキー
		 */
		void LaunchFunction(const wstring& key);

		/**
		 * @brief 関数のリセット
		 *
		 * @param key キー
		 */
		void ResetFunction(const wstring& key);
	};
}
