#pragma once
#include "stdafx.h"

namespace basecross {
	class OnceTrigger :public GameObject {
		using Func = function<void(void)>;
		struct FuncData {
			Func Function;
			bool bOnce;
		};
		// キーとデータのmap
		map<wstring, FuncData> m_funcMap;
	public:
		OnceTrigger(const shared_ptr<Stage>& stage)
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
	};
}
