#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void OnceTriggerObject::OnCreate() {
		GetStage()->SetSharedGameObject(L"OnceTriggerObject", GetThis<OnceTriggerObject>());
		AddComponent<OnceTrigger>();
	}
	void OnceTriggerObject::OnUpdate() {
	}

	void OnceTriggerObject::SetFunction(const wstring& key, Func func) {
		GetComponent<OnceTrigger>()->SetFunction(key, func);
	}

	void OnceTriggerObject::LaunchFunction(const wstring& key) {
		GetComponent<OnceTrigger>()->LaunchFunction(key);
	}

	void OnceTriggerObject::ResetFunction(const wstring& key) {
		GetComponent<OnceTrigger>()->ResetFunction(key);
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
				L"void OnceTriggerObject::LaunchFunction()"
			);
		}
		if (!m_funcMap[key].bOnce) {
			m_funcMap[key].Function();
			m_funcMap[key].bOnce = true;
		}
	}

	void OnceTrigger::ResetFunction(const wstring& key) {
		if (m_funcMap.count(key) == 0) {
			throw BaseException(
				L"指定されたキーがありません",
				L"m_funcMap.count(key) == 0",
				L"void OnceTriggerObject::ResetFunction()"
			);
		}
		m_funcMap[key].bOnce = false;
	}
}