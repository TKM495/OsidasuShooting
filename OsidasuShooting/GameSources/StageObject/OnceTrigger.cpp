#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void OnceTrigger::OnCreate() {
		GetStage()->SetSharedGameObject(L"OnceTrigger", GetThis<OnceTrigger>());
	}
	void OnceTrigger::OnUpdate() {
		for (auto& m : m_funcMap) {
			auto& data = m.second;
			if (data.bOnce) {
				if (data.Function) {
					data.Function();
					data.bOnce = false;
				}
			}
		}
	}

	void OnceTrigger::SetFunction(const wstring& key, Func func) {
		FuncData data = {};
		data.Function = func;
		data.bOnce = false;
		m_funcMap[key] = data;
	}

	void OnceTrigger::LaunchFunction(const wstring& key) {
		if (m_funcMap.count(key) == 0) {
			throw BaseException(
				L"指定されたキーがありません",
				L"m_funcMap.count(key) == 0",
				L"void OnceTrigger::LaunchFunction()"
			);
		}
		m_funcMap[key].bOnce = true;
	}

	void OnceTrigger::ResetFunction(const wstring& key) {
		if (m_funcMap.count(key) == 0) {
			throw BaseException(
				L"指定されたキーがありません",
				L"m_funcMap.count(key) == 0",
				L"void OnceTrigger::ResetFunction()"
			);
		}
		m_funcMap[key].bOnce = false;
	}
}